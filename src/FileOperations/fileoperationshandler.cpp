#include "fileoperationshandler.h"

#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QString>

FileOperationsHandler::FileOperationsHandler(QObject *parent)
    : QObject{parent}
{
    m_savedRoutesListModel = new SavedRoutesListModel( this );
    QString dataPath = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    m_dataPath = dataPath;

    // Create the directory if it does not exist
    QDir dir(dataPath);
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    QString droneDirPath = dataPath + "/Drones";

    // Create the directory if it does not exist
    QDir droneDir(droneDirPath);
    if (!droneDir.exists()) {
        droneDir.mkpath(".");

        // Create initial drones
        DronesAbstractListModel::Drone drone ( "Skydio X10", 45, 40 );
        DronesAbstractListModel::Drone drone2 ( "Skydio X2", 25, 35 );
        saveDrone(drone);
        saveDrone(drone2);
    }

    readSavedRoutes();
}

FileOperationsHandler::~FileOperationsHandler()
{
    m_savedRoutesListModel->deleteLater();
}

bool FileOperationsHandler::saveWayPoints(const QString &name, const  DronesAbstractListModel::Drone &selectedDrone,
                                          const QList<MarkerAbstractListModel::MarkerParams> &wayPoints)
{
    // Check if the file already exists
    QFile file( m_dataPath + QDir::separator() + name + ".json");
    if (file.exists()) {
        return false;
    }

    QJsonObject routeParams;
    int wayPointCount = 0;
    double totalDistance = 0;
    double totalTime = 0;

    // Create a JSON object for the drone
    QJsonObject droneObj;
    droneObj["name"] = selectedDrone.m_name;
    droneObj["maxSpeed"] = selectedDrone.m_maxSpeed;
    droneObj["maxTime"] = selectedDrone.m_maxTime;

    // Prepare a JSON array to hold the waypoints
    QJsonArray waypointsArray;

    // Iterate through the waypoints and convert each to a JSON object
    for (const auto &waypoint : wayPoints) {
        wayPointCount++;
        QJsonObject waypointObj;
        waypointObj["longitude"] = waypoint.m_longitude;
        waypointObj["latitude"] = waypoint.m_latitude;
        waypointObj["speed"] = waypoint.m_speed;
        waypointObj["totalDistanceTraveled"] = waypoint.m_totalDistanceTraveled;
        waypointObj["totalTimeTraveled"] = waypoint.m_totalTimeTraveled;

        waypointsArray.append(waypointObj);

        // Since waypoints accumulate distance/time
        // we can just keep grrabbing the next vals.
        totalDistance = waypoint.m_totalDistanceTraveled;
        totalTime = waypoint.m_totalTimeTraveled;
    }

    routeParams["totalWayPoints"] = wayPointCount;
    routeParams["totalDistance"] = totalDistance;
    routeParams["totalTime"] = totalTime;

    // Combine data into a single JSON object
    QJsonObject mainObj;
    mainObj["quickdata"] = routeParams;
    mainObj["drone"] = droneObj;
    mainObj["waypoints"] = waypointsArray;

    // Wrap the main object in a JSON document
    QJsonDocument doc(mainObj);

    // Open the file for writing
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    file.write(doc.toJson());
    file.close();

    readSavedRoutes();

    return true;
}

void FileOperationsHandler::saveDrone(const DronesAbstractListModel::Drone &drone)
{
    QFile droneFile( m_dataPath + QDir::separator() + "Drones" + QDir::separator() + drone.m_name + ".json" );

    qDebug() << m_dataPath + QDir::separator() + "Drones" + QDir::separator() + drone.m_name + ".json";
    //ensure file does not exist.
    if ( droneFile.exists() )
    {
        qWarning() << "Drone file already exists...";
        return;
    }

    if ( !droneFile.open( QIODevice::WriteOnly ) )
    {
        qWarning() << "Cannot open drone file for writing...";
        return;
    }

    QJsonObject droneJsonObject;
    droneJsonObject["name"] = drone.m_name;
    droneJsonObject["maxSpeed"] = drone.m_maxSpeed;
    droneJsonObject["maxTime"] = drone.m_maxTime;

    QJsonDocument jsonDoc(droneJsonObject);
    droneFile.write( jsonDoc.toJson() );
    droneFile.flush();
    droneFile.close();
}

void FileOperationsHandler::readSavedRoutes()
{
    QList< SavedRoutesListModel::RouteQuickData > savedRoutes;

    QDir savedDir( m_dataPath );
    QStringList jsonFiles = savedDir.entryList(QStringList() << "*.json", QDir::Files);

    foreach (const QString &fileName, jsonFiles) {
        QFile routeFile(savedDir.filePath(fileName));
        if (!routeFile.open(QIODevice::ReadOnly)) {
            qWarning() << "Failed to open file:" << fileName;
            continue;
        }

        QByteArray fileData = routeFile.readAll();
        routeFile.close();

        QString routeName = fileName;
        routeName = routeName.replace(".json", "");

        QJsonDocument doc = QJsonDocument::fromJson(fileData);
        if (doc.isNull()) {
            qWarning() << "Failed to parse the file:" << fileName;
            continue;
        }

        QJsonObject routeJsonObject = doc.object();
        SavedRoutesListModel::RouteQuickData routeData(
            routeName,
            routeJsonObject["drone"].toObject()["name"].toString(),
            routeJsonObject["quickdata"].toObject()["totalDistance"].toDouble(),
            routeJsonObject["quickdata"].toObject()["totalTime"].toDouble(),
            routeJsonObject["waypoints"].toArray().count()
            );

        qDebug() << routeName<< routeJsonObject["drone"].toObject()["name"].toString() <<
            routeJsonObject["quickdata"].toObject()["totalDistance"].toDouble() <<
            routeJsonObject["quickdata"].toObject()["totalTime"].toDouble() <<
            routeJsonObject["waypoints"].toArray().count();

        savedRoutes.append( routeData );
    }

    m_savedRoutesListModel->loadRouteList( savedRoutes );
}

void FileOperationsHandler::removeSavedRoute(const QString &routeName)
{
    QString filePath = m_dataPath + QDir::separator() + routeName + ".json";

    // Check if the file exists
    QFile routeFile(filePath);
    if (!routeFile.exists()) {
        qWarning() << "Route file does not exist:" << filePath;
        return;
    }

    // Remove the file
    if (!routeFile.remove()) {
        qWarning() << "Failed to remove route file:" << filePath;
        return;
    }

    // Refresh saved routes
    readSavedRoutes();
}

QList<DronesAbstractListModel::Drone> FileOperationsHandler::getSavedDrones()
{
    QList<DronesAbstractListModel::Drone> drones;

    QDir directory(m_dataPath + QDir::separator() + "Drones");
    QStringList jsonFiles = directory.entryList(QStringList() << "*.json", QDir::Files);
    foreach (const QString &fileName, jsonFiles) {
        QFile droneFile(directory.filePath(fileName));
        if (!droneFile.open(QIODevice::ReadOnly)) {
            qWarning() << "Failed to open file:" << fileName;
            continue;
        }

        QByteArray fileData = droneFile.readAll();
        droneFile.close();

        QJsonDocument doc = QJsonDocument::fromJson(fileData);
        if (doc.isNull()) {
            qWarning() << "Failed to parse the file:" << fileName;
            continue;
        }

        QJsonObject droneJsonObject = doc.object();
        DronesAbstractListModel::Drone drone(
            droneJsonObject["name"].toString(),
            droneJsonObject["maxSpeed"].toInt(),
            droneJsonObject["maxTime"].toInt()
            );

        drones.append(drone);
    }

    return drones;
}

void FileOperationsHandler::loadRoute(const QString &fileName)
{
    QString filePath = m_dataPath + QDir::separator() + fileName + ".json";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open" << filePath;
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(fileData);
    if (doc.isNull()) {
        qWarning() << "Failed to parse the file:" << filePath;
        return;
    }

    QJsonObject mainObj = doc.object();
    QJsonObject droneObj = mainObj.value("drone").toObject();
    QJsonArray waypointsArray = mainObj.value("waypoints").toArray();

    QList<MarkerAbstractListModel::MarkerParams> wayPointList;
    for (const QJsonValue &value : waypointsArray) {
        QJsonObject waypointObj = value.toObject();
        MarkerAbstractListModel::MarkerParams currentWayPoint(
            waypointObj.value("latitude").toDouble(),
            waypointObj.value("longitude").toDouble(),
            waypointObj.value("speed").toInt(),
            waypointObj.value("totalDistanceTraveled").toDouble(),
            waypointObj.value("totalTimeTraveled").toDouble());

        wayPointList.append(currentWayPoint);
    }

    emit newWayPointsLoaded(wayPointList);
}


SavedRoutesListModel *FileOperationsHandler::savedRoutesModel() const
{
    return m_savedRoutesListModel;
}
