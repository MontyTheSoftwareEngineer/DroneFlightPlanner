import QtQuick 2.15
import QtQuick.Controls 2.15
import "../Components"

Rectangle {
    id: background
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

    Text {
        id: titleText
        anchors {
            top: dialogWindow.top
            topMargin: 10
            horizontalCenter: parent.horizontalCenter
        }

        font.pixelSize: 40
        color: "white"

        text: qsTr("Set Point Speed")
    }

    SpinBox {
        id: speedSpinBox
        width: dialogWindow.width * 0.33
        anchors {
            horizontalCenter: dialogWindow.horizontalCenter
            verticalCenter: dialogWindow.verticalCenter
            margins: 10
        }

        font.pixelSize: 25

        stepSize: 1
        from: 1
        to: {
            var index = droneModel.index(flightPlannerScreen.droneIndex, 0)
            return droneModel.data(index, droneModel.maxSpeedRole)
        }

        value: flightPathManager.markerModel.getMarkerSpeed(
                   flightPlannerScreen.currentSelectedWayPoint)
    }

    StyledButton {
        id: cancelButton
        anchors {
            left: dialogWindow.left
            bottom: dialogWindow.bottom
            margins: 15
        }

        width: dialogWindow.width * 0.25
        height: dialogWindow.height * 0.125

        buttonText: "Cancel"
        onClicked: {
            flightPlannerScreen.currentSelectedWayPoint = -1
            flightPlannerScreen.destroyPopUpDialog()
        }
    }

    StyledButton {
        id: acceptButton
        anchors {
            right: dialogWindow.right
            bottom: dialogWindow.bottom
            margins: 15
        }

        width: dialogWindow.width * 0.25
        height: dialogWindow.height * 0.125

        buttonText: "Accept"
        onClicked: {

            flightPathManager.setMarkerSpeed(
                        flightPlannerScreen.currentSelectedWayPoint,
                        speedSpinBox.value)

            flightPlannerScreen.destroyPopUpDialog()
        }
    }
}
