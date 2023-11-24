#include "markerabstractlistmodel.h"
#include <QDebug>

MarkerAbstractListModel::MarkerAbstractListModel(QObject *parent)
    : QAbstractListModel(parent) {
}

int MarkerAbstractListModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;

    return m_markersList.count();
}

QVariant MarkerAbstractListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    const MarkerParams currentMarkerParam = m_markersList[index.row()];
    switch (role) {
    case LatitudeRole:
        return currentMarkerParam.m_latitude;
    case LongitudeRole:
        return currentMarkerParam.m_longitude;
    case SpeedRole:
        return currentMarkerParam.m_speed;
    case TotalDistanceRole:
        return currentMarkerParam.m_totalDistanceTraveled;
    case TotalTimeRole:
        return currentMarkerParam.m_totalTimeTraveled;
    default:
        return QVariant();
    }
}

void MarkerAbstractListModel::removeMarker(int index)
{
    if (index < 0 || index >= m_markersList.size()) {
        qWarning() << "Index out of range for removal:" << index;
        return;
    }

    beginRemoveRows(QModelIndex(), index, index);
    m_markersList.removeAt(index);
    endRemoveRows();

    //not emiting markerModelChanged here since we want
    //flight path manager to recalculate distances when
    //markers are removed.
}

QHash<int, QByteArray> MarkerAbstractListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[LatitudeRole] = "latitude";
    roles[LongitudeRole] = "longitude";
    roles[SpeedRole] = "speed";
    roles[TotalDistanceRole] = "totaldistance";
    roles[TotalTimeRole] = "totaltime";
    return roles;
}

void MarkerAbstractListModel::addMarker(double latitude, double longitude, int speed, double distance, double totalTime) {
    beginInsertRows(QModelIndex(), m_markersList.count(), m_markersList.count());

    MarkerParams currentMarkerParams( latitude, longitude, speed, distance, totalTime);

    m_markersList.append(currentMarkerParams);
    endInsertRows();

    emit markerModelChanged();
}

void MarkerAbstractListModel::setMarkerDistanceTraveled(int index, double distance)
{
    if (index < 0 || index >= m_markersList.size()) {
        qWarning() << "Index out of range:" << index;
        return;
    }

    MarkerParams &currentMarker = m_markersList[index];
    currentMarker.m_totalDistanceTraveled = distance;

    emit markerModelChanged();
}

void MarkerAbstractListModel::setMarkerTimeTraveled(int index, double time)
{
    if (index < 0 || index >= m_markersList.size()) {
        qWarning() << "Index out of range:" << index;
        return;
    }

    MarkerParams &currentMarker = m_markersList[index];
    currentMarker.m_totalTimeTraveled = time;

    emit markerModelChanged();
}

void MarkerAbstractListModel::setMarkerSpeed(int index, int speed)
{
    if (index < 0 || index >= m_markersList.size()) {
        qWarning() << "Index out of range:" << index;
        return;
    }

    MarkerParams &currentMarker = m_markersList[index];
    currentMarker.m_speed = speed;

    emit markerModelChanged();
}

int MarkerAbstractListModel::getMarkerSpeed(int index)
{
    if (index < 0 || index >= m_markersList.size()) {
        qWarning() << "Index out of range for getMarkerSpeed:" << index;
        return 1;
    }

    QModelIndex modelIndex = createIndex(index, 0);
    return data(modelIndex, SpeedRole).toInt();
}

void MarkerAbstractListModel::checkNewMaxSpeed(int newMaxSpeed)
{
    for ( auto &marker : m_markersList ) {
        if ( marker.m_speed > newMaxSpeed )
            marker.m_speed = newMaxSpeed;
    }

    emit markerModelChanged();
}

QVariantList MarkerAbstractListModel::getMarkers() const {
    QVariantList coords;
    for (const auto &marker : m_markersList) {
        QVariantMap map;
        map["latitude"] = marker.m_latitude;
        map["longitude"] = marker.m_longitude;
        map["speed"] = marker.m_speed;
        map["totaldistance"] = marker.m_totalDistanceTraveled;
        map["totaltime"] = marker.m_totalTimeTraveled;
        coords.append(map);
    }
    return coords;
}

QList<MarkerAbstractListModel::MarkerParams> MarkerAbstractListModel::getAllMarkers() const
{
    return m_markersList;
}

void MarkerAbstractListModel::loadWayPoints(const QList<MarkerParams> & wayPoints)
{
    beginResetModel();
    m_markersList = wayPoints;
    endResetModel();

    emit markerModelChanged();
}

void MarkerAbstractListModel::clear() {
    beginResetModel();
    m_markersList.clear();
    endResetModel();

    emit markerModelChanged();
}
