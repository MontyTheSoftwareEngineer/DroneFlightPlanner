import QtQuick 2.15
import QtQuick.Controls 2.15
import "../Components"

Item {
    id: addDroneScreen
    anchors.fill: parent

    Text {
        id: titleText
        anchors {
            top: addDroneScreen.top
            topMargin: 10
            horizontalCenter: parent.horizontalCenter
        }

        font.pixelSize: 40
        color: "white"

        text: qsTr("Add Drone")
    }

    Rectangle {
        id: droneNameInputBackGround

        anchors {
            horizontalCenter: parent.horizontalCenter
            top: droneNameLabel.bottom
            topMargin: 10
        }

        height: 36
        width: parent.width * 0.5

        color: "#464646"
        radius: 5
    }

    TextInput {
        id: droneNameInput
        anchors.fill: droneNameInputBackGround

        color: "white"
        font.pixelSize: 16

        maximumLength: 22
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        id: droneNameLabel
        anchors {
            top: titleText.bottom
            topMargin: 20
            left: droneNameInputBackGround.left
        }

        color: "white"
        font.pixelSize: 16
        text: "Drone Name"
    }

    Text {
        id: droneSpeedLabel
        anchors {
            top: droneNameInputBackGround.bottom
            topMargin: 20
            left: droneSpeedInputBackGround.left
        }

        color: "white"
        font.pixelSize: 16
        text: "Max Speed (mph)"
    }

    Rectangle {
        id: droneSpeedInputBackGround

        anchors {
            horizontalCenter: parent.horizontalCenter
            top: droneSpeedLabel.bottom
            topMargin: 10
        }

        height: 36
        width: parent.width * 0.5

        color: "#464646"
        radius: 5
    }

    TextInput {
        id: droneSpeedInput
        anchors.fill: droneSpeedInputBackGround

        color: "white"
        font.pixelSize: 16

        validator: RegExpValidator {
            regExp: /^[0-9]*$/
        }

        maximumLength: 3
        inputMethodHints: Qt.ImhDigitsOnly
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        id: droneFlightTimeLabel
        anchors {
            top: droneSpeedInputBackGround.bottom
            topMargin: 20
            left: droneFlightTimeInputBackGround.left
        }

        color: "white"
        font.pixelSize: 16
        text: "Max Flight Time (mins)"
    }

    Rectangle {
        id: droneFlightTimeInputBackGround

        anchors {
            horizontalCenter: parent.horizontalCenter
            top: droneFlightTimeLabel.bottom
            topMargin: 10
        }

        height: 36
        width: parent.width * 0.5

        color: "#464646"
        radius: 5
    }

    TextInput {
        id: droneFlightTimeInput
        anchors.fill: droneFlightTimeInputBackGround

        color: "white"
        font.pixelSize: 16
        validator: RegExpValidator {
            regExp: /^[0-9]*$/
        }

        maximumLength: 2
        inputMethodHints: Qt.ImhDigitsOnly
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    StyledButton {
        id: saveButton
        disabled: droneNameInput.text.trim().length === 0
                  || droneSpeedInput.text.trim().length === 0
                  || droneFlightTimeInput.text.trim().length === 0
        anchors {
            right: addDroneScreen.right
            bottom: addDroneScreen.bottom
            margins: 15
        }

        width: addDroneScreen.width * 0.25
        height: addDroneScreen.height * 0.125

        buttonText: "Save"
        onClicked: {
            droneModel.addDrone(droneNameInput.text.trim(),
                                parseInt(droneSpeedInput.text.trim()),
                                parseInt(droneFlightTimeInput.text.trim()))
            dronesLoader.source = "qrc:/DroneDialog/DronesView.qml"
        }
    }

    StyledButton {
        id: cancelButton
        anchors {
            left: addDroneScreen.left
            bottom: addDroneScreen.bottom
            margins: 15
        }

        width: addDroneScreen.width * 0.25
        height: addDroneScreen.height * 0.125

        buttonText: "Cancel"
        onClicked: {
            dronesLoader.source = "qrc:/DroneDialog/DronesView.qml"
        }
    }
}
