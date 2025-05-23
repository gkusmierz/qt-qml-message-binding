import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Universal

Rectangle {
    
    property string artist: "Some Artist"
    property string title: "Some title"
    property color delegateColor: "#303030"
    property color contrastColor: getContrastColorFromQColor(delegateColor)
    property real delegateProgress: 0.0

    /**
     * @param {color} bgColor    – a QColor/color value (e.g. Qt.rgba(), "#3498db", etc.)
     * @param {number} threshold – optional luminance cutoff (0–1), default is ~0.73
     * @returns {color}          – Qt.rgba(0,0,0,1) or Qt.rgba(1,1,1,1)
     */
    function getContrastColorFromQColor(bgColor, threshold) {
        // default threshold if not passed
        if (typeof threshold !== "number") {
            threshold = 0.73; // ~186/255
        }

        // extract normalized RGB (0–1)
        var r = bgColor.r !== undefined ? bgColor.r : Qt.red(bgColor)   / 255;
        var g = bgColor.g !== undefined ? bgColor.g : Qt.green(bgColor) / 255;
        var b = bgColor.b !== undefined ? bgColor.b : Qt.blue(bgColor)  / 255;

        // compute luminance
        var Y = 0.299*r + 0.587*g + 0.114*b;

        // if bg is light, use black text; otherwise use white
        return (Y > threshold)
            ? Qt.rgba(0, 0, 0, 1)
            : Qt.rgba(1, 1, 1, 1);
    }

    height: 80
    color: Qt.darker(delegateColor)
    
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
        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Text {
                id: artistText
                text: artist
                font.bold: true
                font.pixelSize: 24
                color: contrastColor
                Layout.fillWidth: true
                elide: Text.ElideRight
                //Layout.fillHeight: true
            }
            Text {
                id: titleText
                text: title
                font.bold: false
                font.pixelSize: 18
                color: contrastColor
                Layout.fillWidth: true
                elide: Text.ElideRight
                //Layout.fillHeight: true
            }
        }

        Text {
            // format the progress as a percentage
            text: Math.round(delegateProgress * 100) + "%"
            font.bold: true
            font.pixelSize: 16
            color: contrastColor
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideLeft
        }
        Item {
            Layout.minimumWidth: 8
            Layout.maximumWidth: 8
        }
    }
}
