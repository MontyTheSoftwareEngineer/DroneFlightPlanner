import QtQuick 2.15
import QtQuick.Controls 2.15
import "../Components"

Item {
    id: dronesView
    anchors.fill: parent

    Text {
        id: titleText
        anchors {
            top: dronesView.top
            topMargin: 10
            horizontalCenter: parent.horizontalCenter
        }

        font.pixelSize: 40
        color: "white"

        text: qsTr("Drones")
    }

    Text {
        id: closeButton
        font.pixelSize: 40
        anchors {
            left: dronesView.left
            leftMargin: 30
            top: dronesView.top
            topMargin: 10
        }

        color: "white"

        text: "X"

        MouseArea {
            anchors.fill: parent
            onClicked: mainMenuScreen.destroyPopUpDialog()
        }
    }

    ListView {
        id: dronesListView

        spacing: 15

        model: droneModel
        clip: true

        width: dronesView.width * 0.55

        anchors {
            horizontalCenter: dronesView.horizontalCenter
            top: titleText.bottom
            topMargin: 20
            bottom: addButton.top
            bottomMargin: 20
        }

        delegate: DronesListViewDelegate {}
    }

    StyledButton {
        id: addButton
        anchors {
            horizontalCenter: dronesView.horizontalCenter
            bottom: dronesView.bottom
            margins: 15
        }

        width: dronesView.width * 0.25
        height: dronesView.height * 0.125

        buttonText: "+ Add"
        onClicked: {
            droneDialog.currentlySelectedRouteIndex = -1
            dronesLoader.source = "qrc:/DroneDialog/AddDroneScreen.qml"
        }
    }
}
