#include "dronesabstractlistmodel.h"

DronesAbstractListModel::DronesAbstractListModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int DronesAbstractListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_droneList.count();
}

DronesAbstractListModel::Drone DronesAbstractListModel::getSelectedDrone(const int droneIndex)
{
    if (droneIndex < 0 || droneIndex >= m_droneList.size())
        return Drone("Null", 0, 0);

    return m_droneList.at(droneIndex);
}

QVariant DronesAbstractListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const Drone currentDrone = m_droneList[index.row()];
    switch (role) {
    case DroneName:
        return currentDrone.m_name;
    case MaxSpeedRole:
        return currentDrone.m_maxSpeed;
    case MaxTimeRole:
        return currentDrone.m_maxTime;
    default:
        return QVariant();
    }
}

void DronesAbstractListModel::addDrone(QString droneName, int maxSpeed, int maxTime)
{
    beginInsertRows(QModelIndex(), m_droneList.count(), m_droneList.count());

    Drone newDrone( droneName, maxSpeed, maxTime );

    m_droneList.append(newDrone);
    endInsertRows();

    emit newDroneAdded( newDrone );
    emit dronesChanged();
}

void DronesAbstractListModel::populateDroneList(QList<Drone> savedDroneList)
{
    beginResetModel();
    m_droneList = savedDroneList;
    endResetModel();
}

QHash<int, QByteArray> DronesAbstractListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[DroneName] = "dronename";
    roles[MaxSpeedRole] = "maxspeed";
    roles[MaxTimeRole] = "maxtime";
    return roles;
}
