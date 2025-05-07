import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    visible: true
    width: 360
    height: 400
    title: "Message Model Example"

    function addMessage(inputText) {
        messageModel.addMessage("User", inputText)
        inputField.text = ""
    }

    Rectangle {
        anchors.fill: parent
        anchors.margins: 10

        RowLayout {
            id: toolbarRow
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            TextField {
                id: inputField
                placeholderText: "Enter a message"
                Layout.fillWidth: true

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
            }
            Button {
                text: "Random"
                onClicked: {
                    messageModel.random();
                }
            }
        }

        ListView {
            id: listView
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: toolbarRow.top
            height: parent.height - 100
            model: messageModel
            spacing: 5
            delegate: MessageDelegate {
                delegateAuthor: model.author
                delegateText: model.text
                delegateProgress: model.progress
            }
        }
    }
}
