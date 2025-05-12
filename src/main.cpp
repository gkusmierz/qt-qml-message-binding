#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "librarymodel.h"
#include "playlistmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    LibraryModel library{"/Users/gk/Temp/20250314.mldb"};
    engine.rootContext()->setContextProperty("library", &library);

    PlaylistModel playlist;
    engine.rootContext()->setContextProperty("playlist", &playlist);

    // Load the main qml file
    const QUrl url("qrc:/main.qml");
    engine.load(url);

    return app.exec();
}
