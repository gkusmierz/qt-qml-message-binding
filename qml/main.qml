import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Universal

ApplicationWindow {
    visible: true
    width: 600
    height: 600
    title: "Message Model Example"

    background: Rectangle {
        color: Universal.background
        anchors.fill: parent
    }

    function addMessage(inputText) {
        messageModel.addMessage("User", inputText, )
        toolbarRow.blah = ""
    }

    Rectangle {
        anchors.fill: parent
        anchors.margins: 5
        color: "#151515"
        border.width: 0

        MessageToolbar {
            id: toolbarRow
        }

        ListView {
            id: listView
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: toolbarRow.top
            anchors.margins: 8
            boundsBehavior: ListView.StopAtBounds
            height: parent.height - 100
            model: messageModel
            spacing: 2
            clip: true
            delegate: MessageDelegate {
                delegateAuthor: model.author
                delegateText: model.text
                delegateColor: model.color
                delegateProgress: model.progress
                width: listView.width
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        messageModel.random(model.index);
                    }
                }
            }
            ScrollBar.vertical: ScrollBar {
                id: scrollBar
                width: 16
                opacity: 0.5
            }

        }
    }
}
