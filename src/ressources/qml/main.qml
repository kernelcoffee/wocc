import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import Qt.labs.settings 1.0
import QtQml 2.2

import Wocc 1.0

import "."

ApplicationWindow {
    id: root
    title: "Wocc"
    visible: true
    minimumHeight: 600
    minimumWidth: 800

    property CursestoreController curse: _cursestore

    Settings {
        property alias x: root.x
        property alias y: root.y
        property alias width: root.width
        property alias height: root.height
    }

    Item {
        anchors.fill: parent

        SidePanel {
            id: sidePanel
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
        }

        Item {
            anchors.left: sidePanel.right
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.margins: 10

            SwipeView {
                id: stackView
                anchors.fill: parent
                currentIndex: sidePanel.index
                interactive: false
                clip: true

                Dashboard {
                    id: dashboard
                    store: root.curse
                }

                LibraryView {
                    id: installedTab
                    store: curse
                    model: curse.wowInstalledModel
                }

                LibraryView {
                    id: libraryTab
                    store: curse
                    model: curse.wowModel
                }
            }
        }
    }
}

