/******************************************************************************
 *
 * @file flightpathmanager.h
 *
* @brief The FlightPathManager class
 *
 * This class manages the flight path and interacts with the marker model
 * to manipulate and retrieve marker data.
 *
 * @author              Hai Pham
 * @copyright   (Copyright © 2023 Hai Pham. All rights reserved.
 *
 */

#ifndef FLIGHTPATHMANAGER_H
#define FLIGHTPATHMANAGER_H

#include <QObject>
#include "MapMarkers/markerabstractlistmodel.h"

class FlightPathManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(MarkerAbstractListModel * markerModel READ markerModel CONSTANT)
public:
    /**
     * @brief Constructor for FlightPathManager.
     * @param parent The parent QObject.
     */
    explicit FlightPathManager(QObject *parent = nullptr );

    /**
     * @brief Destructor for FlightPathManager.
     */
    ~FlightPathManager();

    /**
     * @brief Getter for the marker model.
     * @return Pointer to the MarkerAbstractListModel.
     */
    MarkerAbstractListModel *markerModel() const;

    /**
     * @brief Adds a new marker to the model.
     * @param latitude The latitude of the new marker.
     * @param longitude The longitude of the new marker.
     * @param speed The speed of the new marker.
     */
    Q_INVOKABLE void addMarker(double latitude, double longitude, int speed);

    /**
     * @brief Removes a marker from the model.
     * @param index The index of the marker to remove.
     */
    Q_INVOKABLE void removeMarker(int index);


    /**
     * @brief Sets the speed of a marker.
     * @param index The index of the marker to update.
     * @param speed The new speed value for the marker.
     */
    Q_INVOKABLE void setMarkerSpeed( int index, int speed);


    /**
     * @brief Saves current waypoints to file.
     * @param fileName the name of the file.
     */
    Q_INVOKABLE void saveWayPointsToFile(const QString & fileName, const int droneIndex);

    /**
     * @brief Resets Flight Path Manager.
     */
    Q_INVOKABLE void reset();

public slots:
    /**
     * @brief Slot to load saved waypoints.
     * @param wayPoints QList of MarkerParams containing saved waypoints.
     */
    void loadWayPoints(const QList<MarkerAbstractListModel::MarkerParams> &wayPoints );

signals:

private:
    double calculateHaversineDistance( const double latitudePoint1, const double longitudePoint1,
                                        const double latitudePoint2, const double longitudePoint2 );

    void reCalulateDistanceAndTime();

    MarkerAbstractListModel *m_markerModel;
};

#endif // FLIGHTPATHMANAGER_H
