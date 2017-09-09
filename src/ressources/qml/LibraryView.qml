import QtQuick 2.9
import QtQuick.Controls 1.4 as Controls1
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtQuick.Layouts 1.3

import Wocc 1.0

Controls1.TableView {
    id: listView
    property CurseStore store
    property alias model: listView.model

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
    Controls1.TableViewColumn {
        role: "Authors"
        title: "Version Available"
        delegate: Label {
            text: styleData.value
            color: "black"
        }
    }
    Controls1.TableViewColumn {
        role: ""
        title: "Action"
        delegate: Button {
            text: qsTr("Install")
            onClicked: {
                console.log(currentRow)
                store.worldOfWarcraft.install(store.wowModel.getAddon(currentRow));
            }
        }
    }
}
