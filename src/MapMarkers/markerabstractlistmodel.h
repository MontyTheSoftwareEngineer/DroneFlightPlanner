/******************************************************************************
 *
 * @file markerabstractlistmodel.h
 *
 *@brief The MarkerAbstractListModel class
 *
 * This class represents a model for marker data in a list format.
 * Each marker has a latitude, longitude, and speed.
 *
 * @author              Hai Pham
 * @copyright   (Copyright © 2023 Hai Pham. All rights reserved.
 *
 */

#ifndef MARKERABSTRACTLISTMODEL_H
#define MARKERABSTRACTLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>

class MarkerAbstractListModel : public QAbstractListModel
{
    Q_OBJECT
public:

    /**
     * @brief Struct to hold marker parameters.
     */
    struct MarkerParams {
        double m_longitude;
        double m_latitude;
        int m_speed;
        double m_totalDistanceTraveled;
        double m_totalTimeTraveled;

        /**
         * @brief Constructor for MarkerParams.
         * @param lat Latitude of the marker.
         * @param longi Longitude of the marker.
         * @param speed Speed associated with the marker.
         * @param distanceTraveled Total distance traveled to point.
         * @param timeTraveled Total time traveled to point.
         */
        MarkerParams( double lat, double longi, int speed, double distanceTraveled, double timeTraveled )
        {
            m_longitude = longi;
            m_latitude = lat;
            m_speed = speed;
            m_totalDistanceTraveled = distanceTraveled;
            m_totalTimeTraveled = timeTraveled;
        }
    };

    /**
     * @brief Enum for marker roles.
     */
    enum MarkerRoles {
        LatitudeRole = Qt::UserRole + 1,
        LongitudeRole,
        SpeedRole,
        TotalDistanceRole,
        TotalTimeRole
    };

    /**
     * @brief Constructor for MarkerAbstractListModel.
     * @param parent The parent QObject.
     */
    MarkerAbstractListModel(QObject *parent = nullptr);

    /**
     * @brief Clears all markers from the model.
     */
    void clear();

    /**
     * @brief Returns the number of rows in the model.
     * @param parent The parent index.
     * @return The number of markers.
     */
    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /**
     * @brief Retrieves data from the model.
     * @param index The index of the item.
     * @param role The role for which data is required.
     * @return The data stored under the given role for the item referred to by the index.
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /**
     * @brief Removes a marker from the model.
     * @param index The index of the marker to remove.
     */
    void removeMarker(int index);

    /**
     * @brief Adds a new marker to the model.
     * @param latitude The latitude of the new marker.
     * @param longitude The longitude of the new marker.
     * @param speed The speed of the new marker.
     * @param distance Total distance traveled since the first marker.
     * @param totalTime Total time traveled since the first marker.
     */
    void addMarker(double latitude, double longitude, int speed, double distance, double totalTime);

    /**
     * @brief Sets the distance traveled of a marker.
     * @param index The index of the marker to update.
     * @param distance The totalDistance value for the marker.
     */
     void setMarkerDistanceTraveled( int index, double distance);

    /**
     * @brief Sets the time traveled of a marker.
     * @param index The index of the marker to update.
     * @param time The total time value for the marker.
     */
    void setMarkerTimeTraveled( int index, double time);

    /**
     * @brief Sets the speed of a marker.
     * @param index The index of the marker to update.
     * @param speed The new speed value for the marker.
     */
    void setMarkerSpeed( int index, int speed);

    /**
     * @brief Gets the speed of a marker at a specific index.
     * @param index The index of the marker.
     * @return The speed of the marker.
     */
    Q_INVOKABLE int getMarkerSpeed(int index);

    /**
     * @brief Checks and updates the markers' speeds if they exceed a new maximum speed.
     * @param newMaxSpeed The new maximum speed to enforce.
     */
    Q_INVOKABLE void checkNewMaxSpeed( int newMaxSpeed );

    /**
     * @brief Gets a list of coordinates for all markers.
     * @return A QVariantList containing the coordinates of all markers.
     */
    Q_INVOKABLE QVariantList getMarkers() const;

    /**
     * @brief Getter for cached data.
     * @return A QList containing all MarkerParams in data model.
     */
    QList< MarkerParams> getAllMarkers() const;

    /**
     * @brief Load cached data with saved waypoints.
     * @param wayPoints A QList containing waypoints.
     */
    void loadWayPoints(const QList<MarkerParams> &wayPoints);
protected:
    /**
     * @brief Provides the role names to be used in QML.
     * @return A hash table of role names.
     */
    QHash<int, QByteArray> roleNames() const override;

signals:

    /**
     * @brief Signal emitted when the marker model has changed.
     */
    void markerModelChanged();

private:
    QList<MarkerParams> m_markersList;
};

#endif // MARKERABSTRACTLISTMODEL_H
