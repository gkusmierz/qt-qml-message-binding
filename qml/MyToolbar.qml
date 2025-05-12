import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Universal

RowLayout {
    id: toolbarRow

    height: 45
    spacing: 5
    z: 1
    
    Button {
        text: "Add"
        onClicked: {
            var randomItem = library.randomItem();
            console.log(randomItem)
            playlist.addPlaylistItem(randomItem.artist, randomItem.title, 0.0, 0.0, 0.0, 0.0, randomItem.duration, "red");
        }
        Layout.fillHeight: true
        Layout.preferredWidth: 100
        font.bold: true
    }
    Button {
        text: "Random\nProgress"
        onClicked: {
            playlist.randomProgress();
        }
        Layout.fillHeight: true
        Layout.preferredWidth: 100
        font.bold: true
    }
    Button {
        text: "Random\nColor"
        onClicked: {
            playlist.randomColor();
        }
        Layout.fillHeight: true
        Layout.preferredWidth: 100
        font.bold: true
    }
    Item {
        Layout.fillWidth: true
    }
}
