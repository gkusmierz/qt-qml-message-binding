import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    property string delegateAuthor: ""
    property string delegateText: ""
    property real delegateProgress: 0.0

    width: parent.width
    height: 50
    color: "white"
    
    RowLayout {
        spacing: 10
        anchors.fill: parent
        Text {
            text: delegateAuthor + ": "
            font.bold: true
        }
        Text {
            text: delegateText
            Layout.fillWidth: true
        }
        Text {
            // format the progress as a percentage
            text: Math.round(delegateProgress * 100) + "%"
        }
    }
}
