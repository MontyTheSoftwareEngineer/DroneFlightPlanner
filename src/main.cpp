#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "FlightPathManager/flightpathmanager.h"
#include "Drones/dronesabstractlistmodel.h"
#include "FileOperations/fileoperationshandler.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    FileOperationsHandler &fileIOHandler = FileOperationsHandler::instance();

    DronesAbstractListModel& droneModel = DronesAbstractListModel::instance();

    FlightPathManager flightPathManager;

    // Connection to save new drone when it is added.
    QObject::connect( &droneModel, &DronesAbstractListModel::newDroneAdded, &fileIOHandler, &FileOperationsHandler::saveDrone );

    // Populate drone list.
    droneModel.populateDroneList(fileIOHandler.getSavedDrones());

    // Connection for loading waypoint file.
    QObject::connect( &fileIOHandler, &FileOperationsHandler::newWayPointsLoaded, &flightPathManager, &FlightPathManager::loadWayPoints);

    engine.rootContext()->setContextProperty("droneModel", &DronesAbstractListModel::instance());
    engine.rootContext()->setContextProperty("fileHandler", &FileOperationsHandler::instance());
    engine.rootContext()->setContextProperty("flightPathManager", &flightPathManager);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
