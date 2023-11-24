import QtQuick 2.15
import QtQuick.Controls 2.15
import "../Components"

Rectangle {
    id: confirmBackDialog
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

        text: qsTr("Warning: Discard Data?")
    }

    Text {
        id: descriptionText
        anchors {
            top: titleText.bottom
            bottom: cancelButton.top
            topMargin: 20
            bottomMargin: 20
            horizontalCenter: parent.horizontalCenter
        }
        width: dialogWindow.width
        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.Wrap
        color: "white"
        font.pixelSize: 16
        text: qsTr("Going back will discard all unsaved path data. Are you sure you want to proceed?")
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

        buttonText: "Discard"
        onClicked: {
            flightPathManager.reset()
            flightPlannerScreen.destroyPopUpDialog()
            stackView.pop()
        }
    }
}
