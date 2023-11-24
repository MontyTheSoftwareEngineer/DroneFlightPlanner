import QtQuick 2.15
import QtQuick.Layouts 1.15
import "../Components"

Rectangle {
    id: menuPanel

    color: "#050505"

    Text {
        id: titleText
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 25
        }

        font.pixelSize: 40
        color: "white"
        text: qsTr("Drone Flight Planner")
    }

    ColumnLayout {
        id: buttonLayout

        anchors {
            top: titleText.bottom
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
            topMargin: 65
            bottomMargin: 65
        }

        width: parent.width * 0.65

        spacing: 65

        MenuButton {
            id: createButton
            imageSource: "qrc:/assets/createIcon.png"
            buttonText: "Create"
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height / 4 - buttonLayout.spacing
            onClicked: {
                stackView.push(
                            "qrc:/FlightPlannerScreen/FlightPlannerScreen.qml")
            }
        }

        MenuButton {
            id: routesButton
            imageSource: "qrc:/assets/routesIcon.png"
            buttonText: "Routes"
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height / 4 - buttonLayout.spacing

            onClicked: {
                stackView.push("qrc:/RoutesScreen/RoutesScreen.qml")
            }
        }

        MenuButton {
            id: dronesButton
            imageSource: "qrc:/assets/dronesIcon.png"
            buttonText: "Drones"
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height / 4 - buttonLayout.spacing
            onClicked: {
                mainMenuScreen.createDroneDiaog()
            }
        }

        MenuButton {
            id: aboutButton
            imageSource: "qrc:/assets/aboutIcon.png"
            buttonText: "About"
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height / 4 - buttonLayout.spacing
            onClicked: {
                mainMenuScreen.createAboutDialog()
            }
        }
    }
}
