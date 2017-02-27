import QtQuick 2.7
import QtQuick.Controls 2.0
import Qt.labs.settings 1.0

ApplicationWindow {
    id: root
    title: "Wocc"
    visible: true
    minimumHeight: 600
    minimumWidth: 800

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
        model: db.model
        delegate: Rectangle {
            anchors.left: parent.left
            anchors.right: parent.right
            height: 40
            color: "lightsteelblue"
            Label {
                text: name
            }
        }
    }
}
