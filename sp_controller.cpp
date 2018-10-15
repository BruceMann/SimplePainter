#include "sp_controller.h"

SP_Controller::SP_Controller(QObject* parent):QObject(parent)
{

}

SP_Controller::~SP_Controller()
{

}

void SP_Controller::onMousePressed(int x, int y)
{
    m_mouseAction = 1;
    emit notifyPainterState(m_color);
    emit beginCollectPoint(x,y);
    emit sendData(m_mouseAction,x,y);
}

void SP_Controller::onMouseRelesed(int x, int y)
{
    m_mouseAction = 0;
    emit endCollectPoint(x,y);
    emit sendData(m_mouseAction,x,y);
}

void SP_Controller::onMousePositionChanged(int x, int y)
{
    m_mouseAction = 2;
    emit collectPoint(x,y);
    emit sendData(m_mouseAction,x,y);
}

void SP_Controller::onColorChange(QColor color)
{
    m_color = color;
}

void SP_Controller::UnTodoEventHandler(QList<QPoint> data)
{

}
