import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    visible: true
    width: 360
    height: 400
    title: "Message Model Example"

    Rectangle {
        anchors.fill: parent
        anchors.margins: 10

        RowLayout {
            id: inputRow
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            TextField {
                id: inputField
                placeholderText: "Enter a message"
                Layout.fillWidth: true
            }
            Button {
                text: "Send"
                onClicked: {
                    if (inputField.text.length > 0) {
                        messageModel.addMessage("User", inputField.text)
                        inputField.text = ""
                    }
                }
            }
        }

        ListView {
            id: listView
            anchors.top: input.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: inputRow.top
            height: parent.height - 100
            model: messageModel
            delegate: Rectangle {
                width: parent.width
                height: 50
                color: "lightgray"
                border.width: 1
                border.color: "gray"

                Row {
                    spacing: 10
                    anchors.verticalCenter: parent.verticalCenter
                    Text { text: "[" + author + "]:"; font.bold: true }
                    Text { text: text }
                }
            }
        }
    }
}
