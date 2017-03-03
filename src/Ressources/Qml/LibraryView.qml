import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import Wocc 1.0

Item {
    id: libraryView

    property CurseStoreController store: _database
    property alias model: listView.model

    ListView {
        id: listView
        anchors.fill: parent
        ScrollBar.vertical: ScrollBar { id: scrollBar }
        highlight: Rectangle {color: 'grey'}
        highlightMoveDuration: 10
        delegate: Rectangle {
            anchors.left: parent.left
            anchors.right: parent.right
            height: 30
            color: versionInstalled == versionAvailable ? "transparent" : "lightgreen"
            RowLayout {
                anchors.fill: parent
                Label {
                    text: name
                }
                Label {
                    text: authors
                }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: listView.currentIndex = index
            }
        }
    }
}
