import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Universal

ApplicationWindow {
    visible: true
    width: 360
    height: 400
    title: "Message Model Example"

    background: Rectangle {
        color: Universal.background
        anchors.fill: parent
    }

    function addMessage(inputText) {
        messageModel.addMessage("User", inputText, )
        inputField.text = ""
    }

    Rectangle {
        anchors.fill: parent
        anchors.margins: 5
        color: "#151515"
        border.width: 0

        RowLayout {
            id: toolbarRow
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: 8
            height: 40
            spacing: 5
            z: 1

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
            }
            Button {
                text: "Random"
                onClicked: {
                    messageModel.random();
                }
                Layout.fillHeight: true
            }
        }

        ListView {
            id: listView
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: toolbarRow.top
            anchors.margins: 8
            height: parent.height - 100
            model: messageModel
            spacing: 2
            clip: true
            delegate: MessageDelegate {
                delegateAuthor: model.author
                delegateText: model.text
                delegateProgress: model.progress
                width: listView.width
            }
            ScrollBar.vertical: ScrollBar {
                id: scrollBar
                width: 16
                opacity: 0.5
            }
        }
    }
}
