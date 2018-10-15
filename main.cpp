#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml/QQmlContext>

#include "datamodel.h"
#include "sp_controller.h"
#include "sp_model.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    SP_Model *model = new SP_Model;
    SP_Controller *controller = new SP_Controller;
    model->setController(controller);



    qmlRegisterType<PointData>("DataModel",1,0,"PointData");
    qmlRegisterType<DataModel>("DataModel",1,0,"DataModel");
    qmlRegisterType<SP_Controller>("Controller",1,0,"Controller");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
