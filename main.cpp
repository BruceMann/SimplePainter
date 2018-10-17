#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml/QQmlContext>

#include "datamodel.h"
#include "sp_controller.h"
#include "sp_model.h"
#include "paintedItem.h"
SPController *controller;
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

//    PaintedItem m_painter;
//    engine.rootContext()->setContextProperty("PaintedItem",m_painter);


//    controller.setView(painter);


    //qmlRegisterType<SPController>("Controller",1,0,"Controller");
    qmlRegisterType<PaintedItem>("PaintedItem", 1, 0, "PaintedItem");
    QQmlApplicationEngine engine;
    controller = new SPController;
    engine.rootContext()->setContextProperty("Controller",controller);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
