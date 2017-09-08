import QtQuick 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0

import Wocc 1.0

Item {
    id: homeTab

    property CursestoreController store

    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        selectExisting: false
        selectFolder: true
        selectMultiple: false
        folder: store.wowDir
        onAccepted: {
            store.wowDir = folder
        }
    }

    RowLayout {
        width: parent.width
        TextField {
            id: pathText
            text: curse.wowDir
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
            onClicked: curse.detect()
        }
        Button {
            text: "Refresh"
            onClicked: curse.refresh()
        }
    }
}
