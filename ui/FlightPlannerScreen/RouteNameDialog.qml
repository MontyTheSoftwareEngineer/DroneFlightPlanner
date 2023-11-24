import QtQuick 2.15
import QtQuick.Controls 2.15
import "../Components"

Rectangle {
    id: routeNameDialog
    anchors.fill: parent
    color: Qt.rgba(1, 1, 1, .65)

    MouseArea {
        anchors.fill: parent
    }

    Rectangle {
        id: dialogWindow
        anchors.centerIn: parent

        radius: 5

        height: parent.height * 0.25
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

        text: qsTr("Enter Route Name")
    }

    Rectangle {
        id: nameInputBackground

        anchors {
            top: titleText.bottom
            bottom: cancelButton.top
            horizontalCenter: parent.horizontalCenter
            margins: 15
        }

        width: dialogWindow.width * 0.75

        color: "#464646"
        radius: 5
    }

    TextInput {
        id: nameInput
        anchors.fill: nameInputBackground
        color: "white"
        font.pixelSize: 16

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        maximumLength: 22
    }

    StyledButton {
        id: cancelButton
        anchors {
            left: dialogWindow.left
            bottom: dialogWindow.bottom
            margins: 15
        }

        width: dialogWindow.width * 0.25
        height: dialogWindow.height * 0.25

        buttonText: "Cancel"
        onClicked: {
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
        height: dialogWindow.height * 0.25

        buttonText: "Save"
        onClicked: {
            flightPathManager.saveWayPointsToFile(
                        nameInput.text, flightPlannerScreen.droneIndex)
            flightPathManager.reset()
            stackView.pop()
        }
    }
}
