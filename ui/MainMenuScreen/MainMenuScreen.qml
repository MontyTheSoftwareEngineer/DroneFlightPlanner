import QtQuick 2.15

Item {
    id: mainMenuScreen

    property var popUpDialog: null

    function createDroneDiaog() {
        if (popUpDialog === null) {
            var component = Qt.createComponent(
                        "qrc:/DroneDialog/DroneDialog.qml")
            popUpDialog = component.createObject(mainMenuScreen, {
                                                     "x": 0,
                                                     "y": 0
                                                 })
            if (popUpDialog !== null) {
                popUpDialog.anchors.fill = mainMenuScreen
            }
        }
    }

    function createAboutDialog() {
        if (popUpDialog === null) {
            var component = Qt.createComponent(
                        "qrc:/AboutDialog/AboutDialog.qml")
            popUpDialog = component.createObject(mainMenuScreen, {
                                                     "x": 0,
                                                     "y": 0
                                                 })
            if (popUpDialog !== null) {
                popUpDialog.anchors.fill = mainMenuScreen
            }
        }
    }

    function destroyPopUpDialog() {
        if (popUpDialog !== null) {
            popUpDialog.destroy()
            popUpDialog = null
        }
    }

    MenuPanel {
        id: menuPanel
        width: parent.width * 0.35
        height: parent.height
        anchors {
            left: parent.left
            top: parent.top
        }
    }

    Rectangle {
        id: droneImageBackground

        anchors {
            left: menuPanel.right
            top: parent.top
            right: parent.right
            bottom: parent.bottom
        }

        color: "#000000"

        Image {
            id: droneImage
            anchors.centerIn: parent
            source: "qrc:/assets/skydioDrone.png"
        }
    }
}
