import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Universal

ApplicationWindow {
    visible: true
    width: 600
    height: 600
    title: "BLAH!!!"

    background: Rectangle {
        color: Universal.background
        anchors.fill: parent
    }

    function addMessage(inputText) {
        playlist.addMessage("User", inputText, )
        toolbarRow.blah = ""
    }

    Rectangle {
        anchors.fill: parent
        anchors.margins: 5
        color: "#151515"
        border.width: 0

        MyToolbar {
            id: toolbarRow
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 12
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
            model: playlist
            spacing: 2
            clip: true
            delegate: PlaylistItemDelegate {
                artist: model.artist
                title: model.title
                delegateColor: model.color
                delegateProgress: model.progress
                width: listView.width
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        // Validate index before calling random
                        if (model && model.index !== undefined && model.index >= 0) {
                            // Perform the playlist item randomization
                            playlist.random(model.index)
                        }
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
