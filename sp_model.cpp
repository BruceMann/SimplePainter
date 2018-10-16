#include "sp_model.h"
#include "sp_controller.h"

#include <QDebug>

SPModel::SPModel(QObject *parent)
    :QObject(parent)
{

}

SPModel::SPModel(QObject *parent, SPController *ctr)
    :QObject(parent)
{
    qDebug()<<"SPModel::setController"<<ctr->objectName();
    m_controller = ctr;

        //connect(m_controller,&SP_Controller::undosigal,this,&SPModel::undo);

   // connect(this,&SPModel::UnTodoEvent,m_controller,&SP_Controller::UnTodoEventHandler);

}

SPModel::~SPModel()
{

}

void SPModel::setController(SPController *ctr)
{


}

//开始收集点
void SPModel::onBeginColloctPoint(int x, int y)
{
    if(m_points.empty()){
        //qDebug()<<"onBeginColloctPoint m_points.append("<<x<<" "<<y<<")";
        m_points.append(QPoint(x,y));
    }else{
        //TODO::error 处理
    }
}

//结束收集点过程
void SPModel::onEndColloctPoint(int x, int y)
{
    if(m_points.empty()){
        //TODO::error 处理
    }else{
        ActionData a(m_points,m_color);
        m_UndoStack.push(a);
        //qDebug()<<"onEndColloctPoint m_UndoStack.size("<<m_UndoStack.size()<<")";
        m_points.clear();
    }
}

//收集点过程
void SPModel::onColloctPoint(int x, int y)
{
    if(m_points.empty()){
        //TODO::error 处理
    }else{
        //qDebug()<<"onColloctPoint m_points.append("<<x<<" "<<y<<")";
        m_points.append(QPoint(x,y));
    }
}

void SPModel::undo()
{
    //qDebug()<<"SP_Controller::undo() ccccccccccccccccc";

    if(m_UndoStack.empty()){
        return;
    }
    ActionData temp = m_UndoStack.top();
    m_TodoStack.push(temp);
    m_UndoStack.pop();

    emit UnTodoEvent(temp.points);
}



