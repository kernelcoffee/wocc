import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3

import Wocc 1.0

Item {
    id: libraryView

    property DatabaseController db: _database
    property alias model: listView.model

    ListView {
        id: listView
        anchors.fill: parent
        delegate: Rectangle {
            anchors.left: parent.left
            anchors.right: parent.right
            height: 30
            RowLayout {
                anchors.fill: parent
                Label {
                    text: name
                    color: "black"
                }
                Label {
                    text: authors
                    color: "black"
                }
            }
        }
    }
}
