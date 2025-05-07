import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Effects

ApplicationWindow {
    id: window
    width: 1200
    height: 800
    visible: true
    title: "Qt QML Template"

    Image {
        id: image
        anchors.centerIn: parent
        source: "image://icon/edit_calendar"
        width: 64
        height: 64
        smooth: true
        visible: false
        antialiasing: true
    }

    MultiEffect {
        id: colorOverlay
        source: image
        anchors.fill: image
        colorization: 1.0
        colorizationColor: "red"
    }

}
