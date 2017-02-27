import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import Qt.labs.settings 1.0

import Wocc 1.0

ApplicationWindow {
    id: root
    title: "Wocc"
    visible: true
    minimumHeight: 600
    minimumWidth: 800

    property DatabaseController db: _database

    Settings {
        property alias x: root.x
        property alias y: root.y
        property alias width: root.width
        property alias height: root.height
    }

    Shortcut {
        sequence: StandardKey.Refresh
        onActivated: db.refresh();
    }

    ListView {
        anchors.fill: parent
        model: db.wowModel
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

            border.width: 1
            border.color: "black"
        }
    }
}
