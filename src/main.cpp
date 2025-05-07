#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "messagemodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    MessageModel model;
    engine.rootContext()->setContextProperty("messageModel", &model);

    // Load the main qml file
    const QUrl url("qrc:/main.qml");
    engine.load(url);

    return app.exec();
}
