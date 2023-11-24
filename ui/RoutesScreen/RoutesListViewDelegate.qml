import QtQuick 2.15

Rectangle {
    id: routesListViewDelegate
    property bool currentlySelected: (index === routesScreen.currentlySelectedRouteIndex)
    color: (routesListViewDelegate.currentlySelected ? "#007EC6" : "#464646")
    clip: true
    width: parent.width
    height: 121
    radius: 5

    Text {
        id: routeName
        color: "white"
        font.pixelSize: 16
        anchors {
            left: parent.left
            top: parent.top
            margins: 10
        }
        text: model.name
    }

    Text {
        id: droneName
        color: "white"
        font.pixelSize: 16
        anchors {
            left: parent.left
            leftMargin: 10
            verticalCenter: parent.verticalCenter
        }
        text: qsTr("Drone: ") + model.drone
    }

    Text {
        id: distanceLabel
        color: "white"
        font.pixelSize: 16
        anchors {
            left: parent.left
            bottom: parent.bottom
            margins: 10
        }
        text: model.distance.toFixed(1) + qsTr(" miles")
    }

    Text {
        id: wayPointCountLabel
        color: "white"
        font.pixelSize: 16
        anchors {
            right: parent.right
            rightMargin: 10
            verticalCenter: parent.verticalCenter
        }
        text: model.waypointcount + qsTr(" Waypoints")
    }

    Text {
        id: flightTimeLabel
        color: "white"
        font.pixelSize: 16
        anchors {
            right: parent.right
            bottom: parent.bottom
            margins: 10
        }
        text: "Flight Time: " + model.time.toFixed(1) + " m"
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            if (!routesListViewDelegate.currentlySelected) {
                routesScreen.currentlySelectedRouteIndex = index
                fileHandler.loadRoute(model.name)
            } else
                routesScreen.currentlySelectedRouteIndex = -1
        }
    }

    Image {
        id: deleteButton

        visible: routesListViewDelegate.currentlySelected

        width: parent.height * 0.2
        height: width

        anchors {
            right: parent.right
            top: parent.top
            margins: 5
        }

        MouseArea {
            id: deleteMouseArea
            property bool isPressed: false
            anchors.fill: parent
            onClicked: {
                flightPathManager.reset()
                fileHandler.removeSavedRoute(model.name)
            }
            onPressed: deleteMouseArea.isPressed = true
            onReleased: deleteMouseArea.isPressed = false
        }
        fillMode: Image.PreserveAspectFit
        source: (deleteMouseArea.isPressed ? "qrc:/assets/delete_pressed.png" : "qrc:/assets/delete.png")
    }
}
