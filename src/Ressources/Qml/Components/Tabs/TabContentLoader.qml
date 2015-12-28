import QtQuick 2.5
import Material 0.1

Item {
    id: root

    property string source

    Loader {
        id: contentLoader
        anchors.fill: parent
        asynchronous: true
        source: root.source
        onStatusChanged: console.warn(status)
    }

    ProgressCircle {
        id: contentBusyLoader
        anchors.centerIn: parent
        opacity: 0
    }

    State {
        when: contentLoader.status !== Loader.Ready
        PropertyChanges { target: contentLoader; opacity: 0 }
        PropertyChanges { target: contentBusyLoader; opacity: 1 }
    }
    transitions: [
        Transition {
            NumberAnimation { properties: "opacity"; duration: 250}
        }
    ]
}
