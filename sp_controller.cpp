#include "sp_controller.h"
#include "sp_model.h"
#include "painteditem.h"


#include <QDebug>

SPController::SPController(QObject* parent):QObject(parent)
{
    qDebug()<<"SPController::SPController(QObject* parent):QObject(parent)";
    m_model = new SPModel;

    connect(this,SIGNAL(undosigal()),m_model,SLOT(undo()));
    connect(m_model,&SPModel::UnTodoEvent,this,&SPController::UnTodoEventHandler);
    connect(m_model,&SPModel::pointDataChanged,this,&SPController::onPointDataChanged);
}

SPController::~SPController()
{

}

void SPController::setView(PaintedItem *view)
{
    m_view = view;

    connect(m_view,&PaintedItem::mouseMove,this,&SPController::onMousePositionChanged);
    connect(m_view,&PaintedItem::mousePresse,this,&SPController::onMousePressed);
    connect(m_view,&PaintedItem::mouseRelease,this,&SPController::onMouseRelesed);
}

bool SPController::modelData()
{
    return m_modelData;
}

void SPController::setModelData(bool flag)
{
    m_modelData = flag;
}

void SPController::updateView()
{
    //qDebug()<<"updateView";
    m_view->setStrokes(getStrokes());
    m_view->updateView();
    emit modelDataChanged();
}

const Strokes &SPController::getStrokes()
{
    return m_model->getStrokes();
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

    m_model->onEndColloctPoint(x,y);

    emit sendData(m_mouseAction,x,y);
}

void SPController::onMousePositionChanged(int x, int y)
{
    m_mouseAction = 2;
    m_model->onColloctPoint(x,y);

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

void SPController::onPointDataChanged()
{
    //qDebug()<<"onPointDataChanged";
    updateView();
}
