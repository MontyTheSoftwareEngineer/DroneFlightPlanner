import QtQuick 2.15
import QtQuick.Controls 2.15
import "../Components"

Rectangle {
    id: aboutDialog

    anchors.fill: parent
    color: Qt.rgba(1, 1, 1, .65)

    MouseArea {
        anchors.fill: parent
    }

    Rectangle {
        id: dialogWindow
        anchors.centerIn: parent

        radius: 5

        height: parent.height * 0.65
        width: parent.width * 0.4

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

        text: qsTr("About")
    }

    Text {
        id: writtenByLabel
        anchors {
            top: titleText.bottom
            topMargin: 20
            horizontalCenter: parent.horizontalCenter
        }

        font.pixelSize: 16
        color: "white"

        text: "Written by: Hai Pham | Nov 2023"
    }

    Image {
        id: gmailIcon
        anchors {
            top: writtenByLabel.bottom
            topMargin: 20
            left: dialogWindow.left
            leftMargin: 40
        }

        width: 40
        height: 40

        fillMode: Image.PreserveAspectFit
        source: "qrc:/assets/gmail.png"
    }

    Text {
        id: emailLabel
        anchors {
            verticalCenter: gmailIcon.verticalCenter
            left: gmailIcon.right
            leftMargin: 15
        }

        font.pixelSize: 16
        color: "white"

        text: "ggwphp@gmail.com"
    }

    Image {
        id: websiteIcon
        anchors {
            top: gmailIcon.bottom
            topMargin: 40
            left: dialogWindow.left
            leftMargin: 40
        }

        width: 40
        height: 40

        fillMode: Image.PreserveAspectFit
        source: "qrc:/assets/website.png"
    }

    Text {
        id: websiteLabel
        anchors {
            verticalCenter: websiteIcon.verticalCenter
            left: websiteIcon.right
            leftMargin: 15
        }

        font.pixelSize: 16
        color: "white"

        text: "https://hifam.org"
    }

    Image {
        id: linkedInIcon
        anchors {
            top: websiteIcon.bottom
            topMargin: 40
            left: dialogWindow.left
            leftMargin: 40
        }

        width: 40
        height: 40

        fillMode: Image.PreserveAspectFit
        source: "qrc:/assets/linkedin.png"
    }

    Text {
        id: linkedInLabel
        anchors {
            verticalCenter: linkedInIcon.verticalCenter
            left: linkedInIcon.right
            leftMargin: 15
        }

        font.pixelSize: 16
        color: "white"

        text: "https://linkedin.com/in/montythesoftwareengineer"
    }

    Image {
        id: youtubeIcon
        anchors {
            top: linkedInIcon.bottom
            topMargin: 40
            left: dialogWindow.left
            leftMargin: 40
        }

        width: 40
        height: 40

        fillMode: Image.PreserveAspectFit
        source: "qrc:/assets/youtube.png"
    }

    Text {
        id: youtubeLabel
        anchors {
            verticalCenter: youtubeIcon.verticalCenter
            left: youtubeIcon.right
            leftMargin: 15
        }

        font.pixelSize: 16
        color: "white"

        text: "https://youtube.com/MontyTheSoftwareEngineer"
    }

    Image {
        id: gitHubIcon
        anchors {
            top: youtubeIcon.bottom
            topMargin: 40
            left: dialogWindow.left
            leftMargin: 40
        }

        width: 40
        height: 40

        fillMode: Image.PreserveAspectFit
        source: "qrc:/assets/github.png"
    }

    Text {
        id: githubLabel
        anchors {
            verticalCenter: gitHubIcon.verticalCenter
            left: gitHubIcon.right
            leftMargin: 15
        }

        font.pixelSize: 16
        color: "white"

        text: "https://github.com/MontyTheSoftwareEngineer"
    }

    Text {
        id: closeButton
        font.pixelSize: 40
        anchors {
            left: dialogWindow.left
            leftMargin: 30
            top: dialogWindow.top
            topMargin: 10
        }

        color: "white"

        text: "X"

        MouseArea {
            anchors.fill: parent
            onClicked: mainMenuScreen.destroyPopUpDialog()
        }
    }
}
