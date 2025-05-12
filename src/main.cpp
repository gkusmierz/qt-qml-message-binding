#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "playlistdao.h"
#include "playlistmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    PlaylistDao dao{"/Users/gk/Temp/20250314.mldb"};
    engine.rootContext()->setContextProperty("dao", &dao);

    PlaylistModel playlist;
    engine.rootContext()->setContextProperty("playlist", &playlist);

    // Load the main qml file
    const QUrl url("qrc:/main.qml");
    engine.load(url);

    return app.exec();
}
