import QtQuick 2.0

Rectangle {
    id: styledButton
    property string buttonText: "buttonText"
    property string buttonColor: "#464646"
    property string buttonPressedColor: "#6A6A6A"
    property string buttonTextColor: "white"
    property string buttonDisabledColor: "#A1A0A0"
    property string buttonTextDisabledColor: "#717171"
    property bool pressed: false
    property bool disabled: false
    property int fontSize: 16

    signal clicked

    color: {
        if (styledButton.disabled)
            return buttonDisabledColor

        if (pressed)
            return buttonPressedColor
        else
            return buttonColor
    }

    radius: 5

    Text {
        font.pixelSize: fontSize
        color: (styledButton.disabled ? buttonTextDisabledColor : buttonTextColor)
        anchors.centerIn: parent
        text: buttonText
        horizontalAlignment: Text.AlignHCenter
    }

    MouseArea {
        anchors.fill: parent
        onPressed: {
            if (!styledButton.disabled)
                styledButton.pressed = true
        }
        onReleased: {
            if (!styledButton.disabled)
                styledButton.pressed = false
        }
        onClicked: {
            if (!styledButton.disabled)
                styledButton.clicked()
        }
    }
}
