#include "flightpathmanager.h"
#include <QtMath>

#include "Drones/dronesabstractlistmodel.h"
#include "FileOperations/fileoperationshandler.h"

FlightPathManager::FlightPathManager(QObject *parent)
    : QObject{parent}
{
    m_markerModel = new MarkerAbstractListModel(this);
}

FlightPathManager::~FlightPathManager()
{
    m_markerModel->deleteLater();
}

MarkerAbstractListModel *FlightPathManager::markerModel() const
{
    return m_markerModel;
}

void FlightPathManager::addMarker(double latitude, double longitude, int speed)
{
    int rowCount = m_markerModel->rowCount();

    //if first data point, add with no distance
    if ( rowCount < 1 )
        m_markerModel->addMarker( latitude, longitude, speed, 0, 0);
    else
    {
        //otherwise calculate distance from last point.
        QModelIndex lastIndex = m_markerModel->index(rowCount - 1, 0);
        double prevLat = m_markerModel->data(lastIndex, MarkerAbstractListModel::LatitudeRole).toDouble();
        double prevLong = m_markerModel->data(lastIndex, MarkerAbstractListModel::LongitudeRole).toDouble();

        double distanceTraveledSinceLastPoint = calculateHaversineDistance( latitude, longitude, prevLat, prevLong );

        //1.5 miles = d; 26mph = s
        //h = 1.5/26 = d/s
        //m = h*60;
        double speed = m_markerModel->data(lastIndex, MarkerAbstractListModel::SpeedRole).toDouble();
        double timeTraveledSinceLastPoint = (distanceTraveledSinceLastPoint / speed ) * 60.0;

        double lastPointTravelDistance = m_markerModel->data(lastIndex, MarkerAbstractListModel::TotalDistanceRole).toDouble();
        double lastPointTimeTraveled = m_markerModel->data(lastIndex, MarkerAbstractListModel::TotalTimeRole).toDouble();

        //store TOTAL distance/time traveled since beginning.
        double totalDistanceTraveled = distanceTraveledSinceLastPoint + lastPointTravelDistance;
        double totalTimeTraveled = timeTraveledSinceLastPoint + lastPointTimeTraveled;
        //finally add our new point.
        m_markerModel->addMarker( latitude, longitude, speed, totalDistanceTraveled, totalTimeTraveled);
    }
}

void FlightPathManager::removeMarker(int index)
{
    //first remove marker.
    m_markerModel->removeMarker( index );

    reCalulateDistanceAndTime();
}

void FlightPathManager::setMarkerSpeed(int index, int speed)
{
    m_markerModel->setMarkerSpeed( index, speed );

    reCalulateDistanceAndTime();
}

void FlightPathManager::saveWayPointsToFile(const QString &fileName, const int droneIndex )
{
    DronesAbstractListModel &droneListModel = DronesAbstractListModel::instance();
    DronesAbstractListModel::Drone drone = droneListModel.getSelectedDrone(droneIndex);

    FileOperationsHandler &fileHandler = FileOperationsHandler::instance();

    fileHandler.saveWayPoints( fileName, drone, m_markerModel->getAllMarkers());
}

void FlightPathManager::reset()
{
    m_markerModel->clear();
}

void FlightPathManager::loadWayPoints(const QList<MarkerAbstractListModel::MarkerParams> & wayPoints)
{
    m_markerModel->loadWayPoints( wayPoints );
}

double FlightPathManager::calculateHaversineDistance(const double latitudePoint1, const double longitudePoint1, const double latitudePoint2, const double longitudePoint2)
{
    double LatP1InRadians, LongP1InRadians, LatP2InRadians, LongP2InRadians;

    // Earth radius in miles
    const double EarthRadiusInMiles = 3958.756;

    // Convert latitude and longitude from degrees to radians
    LatP1InRadians = qDegreesToRadians( latitudePoint1 );
    LongP1InRadians = qDegreesToRadians( longitudePoint1 );
    LatP2InRadians = qDegreesToRadians( latitudePoint2 );
    LongP2InRadians = qDegreesToRadians( longitudePoint2 );

    // Differences in latitude and longitude
    double dLat = LatP2InRadians - LatP1InRadians;
    double dLon = LongP2InRadians - LongP1InRadians;

    // Haversine formula
    double a = qSin(dLat / 2) * qSin(dLat / 2) +
               qCos(LatP1InRadians) * qCos(LatP2InRadians) *
                   qSin(dLon / 2) * qSin(dLon / 2);
    double c = 2 * qAtan2(qSqrt(a), qSqrt(1 - a));
    double distance = EarthRadiusInMiles * c;

    // Distance in miles
    return distance;
}

void FlightPathManager::reCalulateDistanceAndTime()
{

    double totalDistance = 0.0;
    double totalTime = 0.0;
    //hodling prev waypoint lat/long.
    double prevLat = 0.0;
    double prevLong = 0.0;

    QVariantList existingMarkers = m_markerModel->getMarkers();
    for (int i = 0; i < existingMarkers.size(); ++i) {
        QVariantMap marker = existingMarkers[i].toMap();
        double latitude = marker["latitude"].toDouble();
        double longitude = marker["longitude"].toDouble();
        double speed = marker["speed"].toDouble();

        if (i == 0) {
            // The first marker's distance is always 0.
            m_markerModel->setMarkerDistanceTraveled(i, 0.0);
            m_markerModel->setMarkerTimeTraveled(i, 0.0);
        } else {
            // Calculate the distance from the previous marker
            double distance = calculateHaversineDistance(prevLat, prevLong, latitude, longitude);
            double time = distance / speed * 60.0;
            totalDistance += distance;
            totalTime += time;
            m_markerModel->setMarkerDistanceTraveled(i, totalDistance);
            m_markerModel->setMarkerTimeTraveled(i, totalTime);
        }

        // Update the previous latitude and longitude
        prevLat = latitude;
        prevLong = longitude;
    }
}
