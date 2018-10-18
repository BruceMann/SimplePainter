#include "sp_controller.h"
#include "sp_model.h"
#include "painteditem.h"
#include "sp_proxy.h"

#include <QDebug>

SPController::SPController(QObject* parent):QObject(parent)
{
    qDebug()<<"SPController::SPController(QObject* parent):QObject(parent)";  

    m_model = new SPModel;
    connect(m_model,&SPModel::pointDataChanged,this,&SPController::onPointDataChanged);

    m_proxy = new SPProxy;
    connect(m_proxy,&SPProxy::reciveDatagrams,this,&SPController::onReceiveDatagrams);
    connect(m_proxy,&SPProxy::statesChange,this,&SPController::onColorChange);
    connect(m_proxy,&SPProxy::undoEvent,this,&SPController::onOtherUndo);
    connect(m_proxy,&SPProxy::clearEvent,this,&SPController::onOtherClear);
}

SPController::~SPController()
{
    qDebug()<<"SPController::~SPController()";
    delete m_model;
    delete m_proxy;
}

void SPController::setView(PaintedItem *view)
{
    m_view = view;
}

void SPController::updateView()
{
    m_view->setStrokes(getStrokes());
    m_view->update();
}

const Strokes &SPController::getStrokes()
{
    return m_model->getStrokes();
}

void SPController::onMousePressed(int x, int y)
{
    m_mouseAction = 1;

    m_model->onBeginColloctPoint(m_model->getUserId(),x,y);

    emit notifyPainterState(m_color);

    m_proxy->sendDatagram(m_model->getUserId(),m_mouseAction,x,y);
}

void SPController::onMouseRelesed(int x, int y)
{
    m_mouseAction = 0;

    m_model->onEndColloctPoint(x,y);

    m_proxy->sendDatagram(m_model->getUserId(),m_mouseAction,x,y);
}

void SPController::onMousePositionChanged(int x, int y)
{
    m_mouseAction = 2;
    m_model->onColloctPoint(x,y);

    m_proxy->sendDatagram(m_model->getUserId(),m_mouseAction,x,y);
}

void SPController::onColorChange(QColor color)
{
    m_color = color;
    m_model->setStates(color);

    m_proxy->sendStatesData(color);
}

void SPController::undo()
{
    qDebug()<<"SPController::undo()";

    m_model->undo(m_model->getUserId());
    m_proxy->undo(m_model->getUserId());
}

void SPController::clear()
{
    qDebug()<<"SPController::clear()";
    m_model->clear();
    m_proxy->clear(m_model->getUserId());
}

void SPController::onPointDataChanged()
{
    //qDebug()<<"onPointDataChanged";
    updateView();
}

void SPController::onReceiveDatagrams(QUuid id,int mouseAct, float x, float y)
{
    qDebug()<<"SPController::onReceiveDatagrams"<<mouseAct<<" "<<x<<" "<<y;

    if(mouseAct==1){
        m_model->onBeginColloctPoint(id,(int)x,(int)y);
    }else if(mouseAct==0){
        m_model->onEndColloctPoint((int)x,(int)y);
    }else if(mouseAct==2){
         m_model->onColloctPoint((int)x,(int)y);
    }
}

void SPController::onOtherUndo(QUuid otherId)
{
    m_model->undo(otherId);
}

void SPController::onOtherClear(QUuid otherId)
{
    Q_UNUSED(otherId);
    m_model->clear();
}

