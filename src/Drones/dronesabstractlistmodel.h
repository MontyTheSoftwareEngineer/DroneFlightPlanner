/******************************************************************************
 *
 * @file dronesabstractlistmodel.h
 *
 *@brief The DronesAbstractListModel class
 *
 * This class represents a model for drones in a list format.
 * Each Drone has a name, max speed, and max time it can travel..
 *
 * @author              Hai Pham
 * @copyright   (Copyright © 2023 Hai Pham. All rights reserved.
 *
 */

#ifndef DRONESABSTRACTLISTMODEL_H
#define DRONESABSTRACTLISTMODEL_H

#include <QAbstractListModel>

class DronesAbstractListModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int droneNameRole READ droneNameRole CONSTANT)
    Q_PROPERTY(int maxSpeedRole READ maxSpeedRole CONSTANT)
    Q_PROPERTY(int maxTimeRole READ maxTimeRole CONSTANT)

public:
    /**
     * @brief Struct to hold a Drone.
     */
    struct Drone {

        int m_maxSpeed;
        int m_maxTime;
        QString m_name;

        /**
         * @brief Constructor for a Drone.
         * @param maxSpeed max speed drone can travel.
         * @param maxTime max time drone can travel.
         */
        Drone( QString name, int maxSpeed, int maxTime )
        {
            m_name = name;
            m_maxSpeed = maxSpeed;
            m_maxTime = maxTime;
        }
    };

    /**
     * @brief Enum for Drone roles.
     */
    enum DroneRoles {
        DroneName = Qt::UserRole + 1,
        MaxSpeedRole,
        MaxTimeRole
    };

    static int droneNameRole() { return DroneName; }
    static int maxSpeedRole() { return MaxSpeedRole; }
    static int maxTimeRole() { return MaxTimeRole; }

    /**
     * @brief Provides access to the singleton instance of the class.
     *
     * This method ensures that only one instance of the class exists.
     * It provides a global point of access to that instance.
     *
     * @return Reference to the singleton instance of DronesAbstractListModel.
     */
    static DronesAbstractListModel& instance() {
        static DronesAbstractListModel _instance;
        return _instance;
    }

    /**
     * @brief Returns the number of rows in the model.
     * @param parent The parent index.
     * @return The number of drones.
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /**
     * @brief Returns selected drone.
     * @param droneIndex index of requested drone.
     */
    Drone getSelectedDrone( const int droneIndex );

    /**
     * @brief Retrieves data from the model.
     * @param index The index of the item.
     * @param role The role for which data is required.
     * @return The data stored under the given role for the item referred to by the index.
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /**
     * @brief Adds a new drone to the model.
     * @param maxSpeed The max speed of the new drone.
     * @param maxTime The max time of the new drone.
     */
    Q_INVOKABLE void addDrone(QString droneName, int maxSpeed, int maxTime);

    /**
     * @brief Loads drone list from saved file.
     * @param savedDroneList List of saved drones to populate model with.
     */
    void populateDroneList(QList< Drone > savedDroneList );

    /**
     * @brief Provides the role names to be used in QML.
     * @return A hash table of role names.
     */
    QHash<int, QByteArray> roleNames() const override;

signals:
    /**
     * @brief Signal emitted when the drone model has changed.
     */
    void dronesChanged();

    /**
     * @brief Signal emitted when a new drone has been created.
     */
    void newDroneAdded( Drone drone );

private:

    /**
     * @brief Private constructor for the singleton pattern.
     *
     * This constructor is private to prevent direct instantiation of the class.
     * Use `instance()` to access the singleton instance of the class.
     *
     * @param parent The parent QObject, default is nullptr.
     */
    explicit DronesAbstractListModel(QObject *parent = nullptr);

    /**
     * @brief Deleted copy constructor.
     *
     * Copy construction is not allowed for singletons.
     */
    DronesAbstractListModel(const DronesAbstractListModel&) = delete;

    /**
     * @brief Deleted assignment operator.
     *
     * Assignment is not allowed for singletons.
     */
    DronesAbstractListModel& operator=(const DronesAbstractListModel&) = delete;

    QList <Drone> m_droneList;
};

#endif // DRONESABSTRACTLISTMODEL_H
