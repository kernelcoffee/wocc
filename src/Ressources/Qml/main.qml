import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4 as Controls1
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import Qt.labs.settings 1.0
import QtQml 2.2
import Wocc 1.0

ApplicationWindow {
    id: root
    title: "Wocc"
    visible: true
    minimumHeight: 600
    minimumWidth: 800

    property CurseStoreController store: _curseStore
    property bool hideSidebar: false
    property alias viewIndex: sideMenuContent.currentIndex

    Settings {
        property alias x: root.x
        property alias y: root.y
        property alias width: root.width
        property alias height: root.height
    }

    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            ToolButton {
                text: "\u25C0"
                rotation: hideSidebar ? 180 : 0
                onClicked: hideSidebar = !hideSidebar
                Behavior on rotation {
                    NumberAnimation {duration: 80}
                }
            }
            Item { Layout.fillWidth: true }
        }
    }

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

    Controls1.SplitView {
        id: splitView
        anchors.fill: parent

        Item {
            id: sideMenu
            Layout.minimumWidth: 200
            Layout.maximumWidth: 400
            clip: true

            Binding {
                id: sideMenuBinding
                target: sideMenuContent
                property: "width"
                when: !hideSidebar
                value: sideMenu.width -10
            }
            Component {
                id: sectionHeading
                Label {
                    text: section
                    font.bold: true
                }
            }

            ListView {
                id: sideMenuContent
                model: sideMenuModel
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
                        onClicked: sideMenuContent.currentIndex = index
                    }
                }

                section.property: "sectionName"
                section.criteria: ViewSection.FullString
                section.delegate: sectionHeading
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
                    NumberAnimation {properties: "Layout.maximumWidth"; duration: 80}
                    NumberAnimation {properties: "Layout.minimumWidth"; duration: 80}
                }
            ]
        }

        StackLayout {
            id: stackView
            currentIndex: root.viewIndex
            Layout.fillWidth: true

            Item {
                id: homeTab
                FileDialog {
                    id: fileDialog
                    title: "Please choose a file"
                    selectExisting: false
                    selectFolder: true
                    selectMultiple: false
                    folder: store.wowDir
                    onAccepted: {
                        console.log("You chose: " + folder)
                        store.wowDir = folder
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
                        text: store.wowDir
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
                        onClicked: store.detect()
                    }
                    Button {
                        text: "Refresh"
                        onClicked: store.refresh()
                    }
                }
            }
            Item {
                id: installedTab
                LibraryView {
                    anchors.fill: parent
                    store: root.store
                    model: root.store.wowInstalledModel
                }
            }
            Item {
                id: libraryTab
                LibraryView {
                    anchors.fill: parent
                    store: root.store
                    model: root.store.wowModel
                }
            }
        }
    }
}

