#include "sp_controller.h"
#include "sp_model.h"
#include <QDebug>

SPController::SPController(QObject* parent):QObject(parent)
{
    m_model = new SPModel;

    connect(this,SIGNAL(undosigal()),m_model,SLOT(undo()));
    connect(m_model,&SPModel::UnTodoEvent,this,&SPController::UnTodoEventHandler);
}

SPController::~SPController()
{

}

void SPController::onMousePressed(int x, int y)
{
    m_mouseAction = 1;

    m_model->onBeginColloctPoint(x,y);

    emit notifyPainterState(m_color);

    emit sendData(m_mouseAction,x,y);
}

void SPController::onMouseRelesed(int x, int y)
{
    m_mouseAction = 0;
    //emit endCollectPoint(x,y);
    m_model->onEndColloctPoint(x,y);

    emit sendData(m_mouseAction,x,y);
}

void SPController::onMousePositionChanged(int x, int y)
{
    m_mouseAction = 2;
    m_model->onColloctPoint(x,y);

//    emit collectPoint(x,y);
    emit sendData(m_mouseAction,x,y);
}

void SPController::onColorChange(QColor color)
{
    m_color = color;
}

void SPController::undo()
{
    qDebug()<<"SPController::undo()";
     m_model->undo();
}

void SPController::UnTodoEventHandler(QList<QPoint> &data)
{
    qDebug()<<"DDDDDDDDDD";
    qDebug()<<"DDDDDDDDDD"<<data.size();

    //Todo 通知view重新绘制
}
