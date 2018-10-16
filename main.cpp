#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml/QQmlContext>

#include "datamodel.h"
#include "sp_controller.h"
#include "sp_model.h"
#include "paintedItem.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);


    SPController *controller = new SPController;

    qmlRegisterType<PointData>("DataModel",1,0,"PointData");
    qmlRegisterType<DataModel>("DataModel",1,0,"DataModel");
    qmlRegisterType<SPController>("Controller",1,0,"Controller");
    qmlRegisterType<SPView>("View",1,0,"View");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
