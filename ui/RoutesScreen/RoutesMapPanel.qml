import QtQuick 2.15
import QtLocation 5.15
import QtPositioning 5.15

Item {
    id: routesMapPanel
    Plugin {
        id: mapPlugin
        name: "osm"
    }

    Connections {
        target: flightPathManager.markerModel
        function onMarkerModelChanged() {
            var markers = flightPathManager.markerModel.getMarkers()
            polyline.visible = false
            polyline.path = markers
            polyline.visible = true

            if (markers.length > 0) {
                var firstMarker = markers[0]
                map.center = QtPositioning.coordinate(firstMarker.latitude,
                                                      firstMarker.longitude)
            }
        }
    }

    Map {
        id: map

        anchors.fill: parent

        plugin: mapPlugin
        center: QtPositioning.coordinate(37.56299, -122.32553)
        zoomLevel: 14

        MapItemView {
            model: flightPathManager.markerModel
            delegate: MapQuickItem {
                id: itemMarker

                coordinate: QtPositioning.coordinate(model.latitude,
                                                     model.longitude)
                sourceItem: Image {
                    source: "qrc:/assets/marker.png"
                    width: 40
                    height: 40
                    anchors.centerIn: parent
                }
            }
        }

        MapPolyline {
            id: polyline

            Connections {
                target: flightPathManager.markerModel
                function onMarkerModelChanged() {
                    polyline.visible = false
                    polyline.path = flightPathManager.markerModel.getMarkers()
                    polyline.visible = true
                }
            }

            line.width: 3
            line.color: "blue"
            path: {
                var pathArray = []
                for (var i = 0; i < flightPathManager.markerModel.getMarkers(
                         ).length; i++) {
                    var coord = flightPathManager.markerModel.getMarkers()[i]
                    pathArray.push(QtPositioning.coordinate(coord.latitude,
                                                            coord.longitude))
                }
                return pathArray
            }
        }
    }
}
