import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Universal

RowLayout {
    id: toolbarRow

    property alias blah: inputField.text

    anchors.left: parent.left
    anchors.right: parent.right
    anchors.bottom: parent.bottom
    anchors.margins: 8
    height: 45
    spacing: 5
    z: 1

    function contrastColor(color) {
        var r = color.red() * 255;
        var g = color.green() * 255;
        var b = color.blue() * 255;
        var luma = (0.299 * r + 0.587 * g + 0.114 * b);
        return luma < 128 ? "white" : "black";
    }
    
    TextField {
        id: inputField
        placeholderText: "Enter a message"
        Layout.fillWidth: true
        Layout.fillHeight: true
        
        Keys.onPressed: (event) => {
                            if (event.key === Qt.Key_Return && text.length > 0) {
                                addMessage(text);
                            }
                        }
        focus: true
    }
    Button {
        text: "Send"
        onClicked: {
            if (inputField.text.length > 0) {
                addMessage(inputField.text)
            }
        }
        Layout.fillHeight: true
        Layout.preferredWidth: 100
        palette {
                                          button: "yellow"
                                      }
    }
    Button {
        text: "Random\nProgress"
        onClicked: {
            playlist.randomProgress();
        }
        Layout.fillHeight: true
        Layout.preferredWidth: 100
    }
    Button {
        text: "Random\nColor"
        onClicked: {
            playlist.randomColor();
        }
        Layout.fillHeight: true
        Layout.preferredWidth: 100
    }
}
