import QtQuick 2.15
import QtQuick.Controls 2.12

Rectangle {
    id: dronesComboBox

    signal droneChanged(real currentDroneIndex)

    radius: 5
    color: "#464646"

    ComboBox {
        id: dcb
        anchors.fill: parent
        model: droneModel
        textRole: "dronename"
        contentItem: Rectangle {
            anchors.fill: parent
            color: "#464646"

            Label {
                id: comboBoxLabel
                text: dcb.currentText
                font.pixelSize: 22
                color: "white"
                anchors {
                    left: parent.left
                    leftMargin: 20
                    verticalCenter: parent.verticalCenter
                }
            }
        }

        onCurrentIndexChanged: {
            dronesComboBox.droneChanged(currentIndex)
        }
        delegate: ItemDelegate {
            width: parent.width

            Rectangle {
                anchors.fill: parent
                color: "#464646"

                Text {
                    id: droneDetails
                    anchors {
                        verticalCenter: parent.verticalCenter
                        left: parent.left
                        leftMargin: 20
                    }

                    font.pixelSize: 22
                    text: model.dronename + "|" + model.maxspeed + "mph|" + model.maxtime + "min"
                    color: "white"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
            }
        }

        popup: Popup {
            y: dcb.height - 1
            width: dcb.width
            implicitHeight: contentItem.implicitHeight
            padding: 1

            contentItem: ListView {
                clip: true
                implicitHeight: contentHeight
                model: dcb.popup.visible ? dcb.delegateModel : null
                currentIndex: dcb.highlightedIndex

                ScrollIndicator.vertical: ScrollIndicator {}
            }

            background: Rectangle {
                border.color: "#21be2b"
                radius: 2
            }
        }
    }
}
