import QtQuick 2.15
import QtQuick.Controls 2.15
import "../Components"

Rectangle {
    id: wayPointListViewDelegate

    property bool currentlySelected: (index === flightPlannerScreen.currentSelectedWayPoint)

    clip: true
    width: parent.width
    height: 121

    radius: 5

    color: {
        //make delegate red if waypoint exceeds flight time
        if (wayPointListPanel.maxTime - model.totaltime < 0) {
            return "#c22404"
        } else
            //make blue if delegate is selected
            (wayPointListViewDelegate.currentlySelected ? "#007EC6" : "#464646")
    }

    Text {
        id: waypointLabelText
        anchors {
            top: parent.top
            left: parent.left
            margins: 5
        }

        color: "white"
        font.pixelSize: 16

        text: qsTr("Waypoint ") + index
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            if (!wayPointListViewDelegate.currentlySelected)
                flightPlannerScreen.currentSelectedWayPoint = index
            else
                flightPlannerScreen.currentSelectedWayPoint = -1
        }
    }

    StyledButton {
        id: speedButton
        anchors {
            left: parent.left
            bottom: parent.bottom
            margins: 10
        }
        buttonColor: "#999999"

        buttonText: "Speed: " + model.speed + "mph"
        width: parent.width * 0.3
        height: parent.height * 0.25
        onClicked: {
            flightPlannerScreen.currentSelectedWayPoint = index
            flightPlannerScreen.createChangeSpeedDialog()
        }
    }

    Image {
        id: deleteButton

        visible: wayPointListViewDelegate.currentlySelected

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
                flightPathManager.removeMarker(index)
            }
            onPressed: deleteMouseArea.isPressed = true
            onReleased: deleteMouseArea.isPressed = false
        }
        fillMode: Image.PreserveAspectFit
        source: (deleteMouseArea.isPressed ? "qrc:/assets/delete_pressed.png" : "qrc:/assets/delete.png")
    }

    Text {
        id: coordsLabel
        anchors {
            horizontalCenter: parent.horizontalCenter
            bottom: distanceTraveledLabel.top
            margins: 5
        }

        color: "white"
        font.pixelSize: 16

        text: model.latitude + "," + model.longitude
    }

    Text {
        id: distanceTraveledLabel
        anchors {
            right: parent.right
            bottom: remainingTimeLabel.top
            margins: 5
        }

        color: "white"
        font.pixelSize: 16

        text: qsTr("Distance: ") + model.totaldistance.toFixed(1) + "mi"
    }

    Text {
        id: remainingTimeLabel
        anchors {
            right: parent.right
            bottom: parent.bottom
            margins: 5
        }

        color: "white"
        font.pixelSize: 16

        text: qsTr("Remaining: ") + (wayPointListPanel.maxTime - model.totaltime).toFixed(
                  1) + "min"
    }
}
