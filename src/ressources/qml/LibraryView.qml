import QtQuick 2.9
import QtQuick.Controls 1.4 as Controls1
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtQuick.Layouts 1.3

import Wocc 1.0

Item {
    id: root

    clip: true

    property CurseController controller
    property alias model: listView.model

    Controls1.TableView {
        id: listView
        anchors.fill: parent

        rowDelegate:  Rectangle {
            id: rowDelegate
            height: 40

            color: Material.background
            states: [
                State {
                    when: styleData.selected
                    PropertyChanges {
                        target: rowDelegate
                        color: "lightsteelblue"
                    }
                }
            ]
        }
        headerDelegate:  Rectangle {
            height: 30

            Label {
                anchors.centerIn: parent
                width: parent.width
                text: styleData.value
                elide: Text.ElideRight
                color: "black"
            }
        }

        Controls1.TableViewColumn {
            role: "name"
            title: "Name"
            delegate: Label {
                text: styleData.value
                color: "black"
            }
        }
        Controls1.TableViewColumn {
            role: "categories"
            title: "Categories"
            delegate: Label {
                text: styleData.value
                color: "black"
            }
        }
        Controls1.TableViewColumn {
            role: "installCount"
            title: "Installed Count"
            delegate: Label {
                text: styleData.value
                color: "black"
            }
        }
    }

    Pane {
        id: detailsPanel
        width: 200
        height: parent.height
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right

        opacity: refreshTimer.running ? 0 : 1
        Material.elevation: 1


        property CurseAddon addon

        onAddonChanged: controller.setDependencyModel(addon)

        Connections {
            target: listView
            onCurrentRowChanged: refreshTimer.restart()
        }

        Timer {
            id: refreshTimer
            interval: 100

            onTriggered: {
                if (listView.currentRow >= 0) {
                    detailsPanel.addon = controller.wowModel.getAddon(listView.currentRow)
                }
            }
        }

        Column {
            id: addonDetailsLayout
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: childrenRect.height

            Label {
                text: detailsPanel.addon.id
                color: "black"
            }
            Label {
                text: detailsPanel.addon.shortName
                color: "black"
            }
            Label {
                text: detailsPanel.addon.summary
                color: "black"
            }
            Label {
                text: detailsPanel.addon.versionAvailable
                color: "black"
            }

            Item {
                width: 1
                height: 10
            }
            Repeater {
                id: depList
                anchors.left: parent.left
                anchors.right: parent.right
                model: controller.dependencyModel

                delegate: Text {
                    text: name
                }
            }
            Button {
                text: qsTr("Install")
                onClicked: {
                    controller.worldOfWarcraft.install(controller.wowModel.getAddon(listView.currentRow));
                }
            }
        }
    }

}
