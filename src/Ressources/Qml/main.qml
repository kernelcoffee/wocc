import QtQuick 2.5
import Material 0.1
import Qt.labs.settings 1.0

import "Components/Tabs"

ApplicationWindow {
    id: root
    title: "Material for QtQuick Demo"
    visible: true
    minimumHeight: Units.dp(600)
    minimumWidth: Units.dp(800)

    Settings {
        property alias x: root.x
        property alias y: root.y
        property alias width: root.width
        property alias height: root.height
    }

    theme {
        primaryColor: Palette.colors["blue"]["500"]
        primaryDarkColor: Palette.colors["blue"]["700"]
        accentColor: Palette.colors["red"]["A200"]
        tabHighlightColor: "white"
        backgroundColor: "white"
    }

    property var sections: [ "Installed", "Available" ]

    initialPage: TabbedPage {
        id: page

        title: "Wocc"

        Repeater {
            model: sections

            delegate: Tab {
                title: sections[index]
                TabContentLoader { source:  Qt.resolvedUrl("Views/%.qml").arg(title) }
            }
        }
    }
}
