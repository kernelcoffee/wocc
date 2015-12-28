import QtQuick 2.5
import Material 0.1
import Material.ListItems 0.1 as ListItem

Item {
    id: installed

    Sidebar {
        id: sidebar

        Column {
            width: parent.width

            Repeater {
                model: ["test1", "test2"]
                delegate: ListItem.Standard {
                    text: modelData
//                    selected: modelData == selectedComponent
//                    onClicked: selectedComponent = modelData
                }
            }
        }
    }

    ListView {
        id: flickable
        anchors {
            left: sidebar.right
            right: parent.right
            top: parent.top
            bottom: parent.bottom
        }

         model: 50
         delegate: Rectangle {
             height: Units.dp(30)
             width: parent.width
             Text {
                 text: index
             }
         }
    }

    Scrollbar {
        flickableItem: flickable
    }

}

