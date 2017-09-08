import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.0

Pane {
    id: root
//    clip: true
    width: 200
    Material.elevation: 10

    padding: 0

    property alias index: contentList.currentIndex

    ListModel {
        id: sideMenuModel
        ListElement {
            name: "Dashboard"
        }
        ListElement {
            name: "Installed"
        }
        ListElement {
            name: "Library"
        }
    }

    Component {
        id: sectionHeading
        Label {
            text: section
            font.bold: true
        }
    }

    ListView {
        id: contentList
        model: sideMenuModel
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        highlight: Rectangle {
            color: 'grey'
        }

        delegate: Label {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 10
            text: name
            MouseArea {
                anchors.fill: parent
                onClicked: contentList.currentIndex = index
            }
        }

        section.property: "sectionName"
        section.criteria: ViewSection.FullString
        section.delegate: sectionHeading
    }
}
