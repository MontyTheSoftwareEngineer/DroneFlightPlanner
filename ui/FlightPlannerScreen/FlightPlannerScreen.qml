import QtQuick 2.15

Item {
    id: flightPlannerScreen

    property int currentSelectedWayPoint: -1

    property int droneIndex: 0

    property var popUpDialog: null

    function createChangeSpeedDialog() {
        if (popUpDialog === null) {
            var component = Qt.createComponent("ChangeSpeedDialog.qml")
            popUpDialog = component.createObject(flightPlannerScreen, {
                                                     "x": 0,
                                                     "y": 0
                                                 })
            if (popUpDialog !== null) {
                popUpDialog.anchors.fill = flightPlannerScreen
            }
        }
    }

    function createConfirmationDialog() {
        if (popUpDialog === null) {
            var component = Qt.createComponent("ConfirmBackDialog.qml")
            popUpDialog = component.createObject(flightPlannerScreen, {
                                                     "x": 0,
                                                     "y": 0
                                                 })
            if (popUpDialog !== null) {
                popUpDialog.anchors.fill = flightPlannerScreen
            }
        }
    }

    function createRouteNameDialog() {
        if (popUpDialog === null) {
            var component = Qt.createComponent("RouteNameDialog.qml")
            popUpDialog = component.createObject(flightPlannerScreen, {
                                                     "x": 0,
                                                     "y": 0
                                                 })
            if (popUpDialog !== null) {
                popUpDialog.anchors.fill = flightPlannerScreen
            }
        }
    }

    function destroyPopUpDialog() {
        if (popUpDialog !== null) {
            popUpDialog.destroy()
            popUpDialog = null
        }
    }

    Connections {
        target: flightPathManager.markerModel
        function onMarkerModelChanged() {
            flightPlannerScreen.currentSelectedWayPoint = -1
        }
    }

    WayPointListPanel {
        id: leftSideBG
        width: parent.width * 0.35
        height: parent.height
        anchors {
            left: parent.left
            top: parent.top
        }
    }

    MapPanel {
        id: mapPanel

        anchors {
            left: leftSideBG.right
            top: parent.top
            right: parent.right
            bottom: parent.bottom
        }
    }
}
