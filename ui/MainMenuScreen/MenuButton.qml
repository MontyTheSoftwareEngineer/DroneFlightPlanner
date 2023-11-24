import QtQuick 2.0

Rectangle {
    id: menuButton
    property string buttonText: "Create"
    property string buttonColor: "#464646"
    property string buttonPressedColor: "#6A6A6A"
    property string buttonTextColor: "white"
    property bool pressed: false
    property bool disabled: false
    property int fontSize: 32
    property string imageSource: "qrc:/assets/createIcon.png"

    signal clicked

    color: {
        if (pressed)
            return buttonPressedColor
        else
            return buttonColor
    }

    radius: 5

    Image {
        id: buttonImage

        anchors {
            left: parent.left
            leftMargin: 20
            verticalCenter: parent.verticalCenter
        }

        source: menuButton.imageSource
        fillMode: Image.PreserveAspectFit
        height: parent.height * 0.6
        width: height
    }

    Text {
        anchors {
            left: buttonImage.right
            leftMargin: 30
            verticalCenter: parent.verticalCenter
        }

        font.pixelSize: fontSize
        color: buttonTextColor
        text: buttonText
        horizontalAlignment: Text.AlignHCenter
    }

    MouseArea {
        anchors.fill: parent
        onPressed: {
            menuButton.pressed = true
        }
        onReleased: {
            menuButton.pressed = false
        }
        onClicked: {
            menuButton.clicked()
        }
    }
}
