import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4 as Controls1
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
    property bool hideSidebar: false

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

    Controls1.SplitView {
        id: splitView
        anchors.fill: parent
        Rectangle {
            id: sideMenu
            Layout.minimumWidth: 200
            Layout.maximumWidth: 400
            clip: true
            color: "lightsteelblue"

            Binding {
                id: sideMenuBinding
                target: sideMenuContent
                property: "width"
                when: !hideSidebar
                value: sideMenu.width
            }

            Item {
                id: sideMenuContent
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                Text {
                    text: "Screen 1"
                    anchors.centerIn: parent
                }

            }

            states: [
                State {
                    when: root.hideSidebar
                    PropertyChanges {
                        target: sideMenu;
                        width: 0
                        Layout.minimumWidth: 0
                        Layout.maximumWidth: 0
                    }
                }
            ]
            transitions: [
                Transition {
                    NumberAnimation {properties: "Layout.maximumWidth"; duration: 1000}
                    NumberAnimation {properties: "Layout.minimumWidth"; duration: 1000}
                }
            ]
        }

        StackLayout {
            id: stackView
            currentIndex: tabbar.currentIndex
            Layout.fillWidth: true

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
                    width: parent.width
                    Button {
                        text: hideSidebar ? "Show" : "Hide"
                        onClicked: hideSidebar = !hideSidebar
                    }
                    TextField {
                        id: pathText
                        text: db.wowDir
                    }
                    Button {
                        text: "Select"
                        onClicked: fileDialog.visible = true
                    }
                    Item {
                        id: spacer
                        Layout.fillWidth: true
                    }

                    Button {
                        text: "Detect"
                        onClicked: db.detect()
                    }
                    Button {
                        text: "Refresh"
                        onClicked: db.refresh()
                    }
                }
            }
            Item {
                id: installedTab
                LibraryView {
                    anchors.fill: parent
                    db: root.db
                    model: root.db.wowInstalledModel
                }
            }
            Item {
                id: libraryTab
                LibraryView {
                    anchors.fill: parent
                    db: root.db
                    model: root.db.wowModel
                }
            }
        }
    }
}

