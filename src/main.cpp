#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "playlistmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    PlaylistModel playlist;
    engine.rootContext()->setContextProperty("playlist", &playlist);

    // Load the main qml file
    const QUrl url("qrc:/main.qml");
    engine.load(url);

    return app.exec();
}
