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
            for (var i = 0; i < 1000; i++) {
                // Get a random item from library
                var randomItem = library.randomItem();
                var artist = randomItem.artist;
                var title = randomItem.title;
                var duration = randomItem.duration;

                console.log(randomItem);

                // Pass values (not the object reference) to the playlist
                playlist.addPlaylistItem(artist, title, 0.0, 0.0, 0.0, 0.0, duration, "red");
            }
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
