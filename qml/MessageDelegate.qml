import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Universal

Rectangle {
    property string delegateAuthor: ""
    property string delegateText: ""
    property color delegateColor: "red"
    property real delegateProgress: 0.0

    height: 64
    color: "#303030"
    
    Rectangle {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        width: Math.max(0, Math.min(1, delegateProgress)) * listView.width
        color: delegateColor
    }

    RowLayout {
        spacing: 10
        anchors.fill: parent
        Item {
            Layout.minimumWidth: 8
        }
        Text {
            text: delegateAuthor
            font.bold: true
            font.pixelSize: 16
            color: Universal.foreground
        }
        Text {
            text: delegateText
            font.pixelSize: 16
            Layout.fillWidth: true
            color: Universal.foreground
        }
        Text {
            // format the progress as a percentage
            text: Math.round(delegateProgress * 100) + "%"
            font.pixelSize: 16
            color: Universal.foreground
        }
        Item {
            Layout.minimumWidth: 8
        }
    }
}
