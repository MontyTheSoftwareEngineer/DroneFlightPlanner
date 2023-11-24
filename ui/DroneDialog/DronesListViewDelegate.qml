import QtQuick 2.15

Rectangle {
    id: dronesListViewDelegate
    property bool currentlySelected: (index === droneDialog.currentlySelectedRouteIndex)
    color: (dronesListViewDelegate.currentlySelected ? "#007EC6" : "#464646")
    clip: true
    width: parent.width
    height: 121
    radius: 5

    Text {
        id: droneName
        color: "white"
        font.pixelSize: 16
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            margins: 10
        }
        text: model.dronename
    }

    Text {
        id: droneSpeed
        color: "white"
        font.pixelSize: 16
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: droneName.bottom
            margins: 15
        }
        text: qsTr("Max Speed: ") + model.maxspeed + "mph"
    }

    Text {
        id: droneFlightTime
        color: "white"
        font.pixelSize: 16
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: droneSpeed.bottom
            margins: 15
        }
        text: qsTr("Max Flight: ") + model.maxtime + "min"
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            if (!dronesListViewDelegate.currentlySelected) {
                droneDialog.currentlySelectedRouteIndex = index
            } else
                droneDialog.currentlySelectedRouteIndex = -1
        }
    }

    Image {
        id: deleteButton

        visible: dronesListViewDelegate.currentlySelected

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
                droneDialog.currentlySelectedRouteIndex = -1
            }
            onPressed: deleteMouseArea.isPressed = true
            onReleased: deleteMouseArea.isPressed = false
        }
        fillMode: Image.PreserveAspectFit
        source: (deleteMouseArea.isPressed ? "qrc:/assets/delete_pressed.png" : "qrc:/assets/delete.png")
    }
}
