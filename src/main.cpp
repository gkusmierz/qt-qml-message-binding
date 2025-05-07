#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSettings>

#include "iconprovider.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // Set the application icon provider
    engine.addImageProvider("icon", new IconProvider(":/MaterialIconsSharp-Regular.otf", ":/MaterialIconsSharp-Regular.codepoints"));

    // Load the main qml file
    const QUrl url("qrc:/main.qml");
    engine.load(url);

    return app.exec();
}
