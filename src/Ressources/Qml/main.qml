import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
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

    header: TabBar {
        id: tabbar
        width: parent.width
        position: TabBar.Header

        TabButton {
            text: qsTr("Home")
        }
        TabButton {
            text: qsTr("Installed")
        }
        TabButton {
            text: qsTr("Library")
        }
    }

    StackLayout {
        id: stackView
        currentIndex: tabbar.currentIndex
        anchors.fill: parent
        Item {
            id: homeTab
            FileDialog {
                id: fileDialog
                title: "Please choose a file"
                selectExisting: false
                selectFolder: true
                selectMultiple: false
                folder: db.wowDir
                onAccepted: {
                    console.log("You chose: " + folder)
                    db.wowDir = folder
                }
                onRejected: {
                    console.log("Canceled")
                }
            }
            RowLayout {
            TextField {
                id: pathText
                anchors.centerIn: parent
                text: db.wowDir
            }
            Button {
                text: "chose"
                onClicked: fileDialog.visible = true
            }

            Button {
                text: "detect"
                onClicked: db.detect()
            }
            }

        }
        Item {
            id: installedTab
        }
        Item {
            id: libraryTab
            LibraryView {
                anchors.fill: parent
                db: root.db
            }
        }
    }
}
