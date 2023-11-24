import QtQuick 2.15
import QtQuick.Controls 2.15
import "../Components"

Rectangle {
    id: droneDialog
    property int currentlySelectedRouteIndex: -1

    anchors.fill: parent
    color: Qt.rgba(1, 1, 1, .65)

    MouseArea {
        anchors.fill: parent
    }

    Rectangle {
        id: dialogWindow
        anchors.centerIn: parent

        radius: 5

        height: parent.height * 0.5
        width: parent.width * 0.5

        color: "#050505"
    }

    Loader {
        id: dronesLoader
        anchors.fill: dialogWindow
        source: "qrc:/DroneDialog/DronesView.qml"
    }
}
