#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml/QQmlContext>

#include "datamodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<PointData>("DataModel",1,0,"PointData");
    qmlRegisterType<DataModel>("DataModel",1,0,"DataModel");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
