/******************************************************************************
 *
 * @file fileoperationshandler.h
 *
 *@brief The FileOperationsHandler class
 *
 * This class handles reading and writing of persident data storage to disk.
 *
 * @author              Hai Pham
 * @copyright   (Copyright © 2023 Hai Pham. All rights reserved.
 *
 */

#ifndef FILEOPERATIONSHANDLER_H
#define FILEOPERATIONSHANDLER_H

#include <QObject>
#include <QJsonDocument>

#include "MapMarkers/markerabstractlistmodel.h"
#include "Drones/dronesabstractlistmodel.h"
#include "savedrouteslistmodel.h"

class FileOperationsHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(SavedRoutesListModel * savedRoutesModel READ savedRoutesModel CONSTANT)
public:

    /**
     * @brief Provides access to the singleton instance of the class.
     *
     * This method ensures that only one instance of the class exists.
     * It provides a global point of access to that instance.
     *
     * @return Reference to the singleton instance of FileOperationsHandler.
     */
    static FileOperationsHandler& instance() {
        static FileOperationsHandler _instance;
        return _instance;
    }

    /**
     * @brief Destructor for FileOperationsHandler.
     **/
    ~FileOperationsHandler();

    /**
     * @brief Saves a list of waypoints, along with associated drone data, to a file.
     *
     * @param name The name of the route to be saved.
     * @param selectedDrone The drone associated with the waypoints.
     * @param wayPoints A list of waypoints to be saved.
     * @return Returns true if the waypoints are successfully saved, false otherwise.
     */
    bool saveWayPoints( const QString &name, const DronesAbstractListModel::Drone & selectedDrone,
                       const QList< MarkerAbstractListModel::MarkerParams> & wayPoints );

    /**
     * @brief Retrieves a list of saved drones from persistent storage.
     *
     * @return A list of drones retrieved from storage.
     */
    QList< DronesAbstractListModel::Drone> getSavedDrones();

    /**
     * @brief Reads and processes a file containing route data.
     *
     * @param fileName The name of the file to be read.
     */
    Q_INVOKABLE void loadRoute( const QString & fileName );

    /**
     * @brief Getter for the saved routes model.
     * @return Pointer to the SavedRoutesListModel.
     */
    SavedRoutesListModel *savedRoutesModel() const;

public slots:
    /**
     * @brief Slot to handle the saving of a drone to persistent storage.
     *
     * @param drone The drone to be saved.
     */
    void saveDrone( const DronesAbstractListModel::Drone & drone );

    /**
     * @brief Slot to read saved routes from persistent storage.
     */
    void readSavedRoutes();

    /**
     * @brief Slot to remove saved route from persistent storage.
     *
     * @param routeName Name of route to be removed.
     */
    void removeSavedRoute( const QString & routeName );
signals:
    void newWayPointsLoaded( QList< MarkerAbstractListModel::MarkerParams > wayPoints );

private:
    /**
     * @brief Private constructor for the singleton pattern.
     *
     * This constructor is private to prevent direct instantiation of the class.
     * Use `instance()` to access the singleton instance of the class.
     *
     * @param parent The parent QObject, default is nullptr.
     */
    explicit FileOperationsHandler(QObject *parent = nullptr);

    /**
     * @brief Deleted copy constructor.
     *
     * Copy construction is not allowed for singletons.
     */
    FileOperationsHandler(const FileOperationsHandler&) = delete;

    /**
     * @brief Deleted assignment operator.
     *
     * Assignment is not allowed for singletons.
     */
    FileOperationsHandler& operator=(const FileOperationsHandler&) = delete;

    QString m_dataPath;
    SavedRoutesListModel * m_savedRoutesListModel;
};

#endif // FILEOPERATIONSHANDLER_H
