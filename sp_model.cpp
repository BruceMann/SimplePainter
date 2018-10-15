#include "sp_model.h"
#include "sp_controller.h"

#include <QDebug>

SP_Model::SP_Model(QObject *parent)
    :QObject(parent)
{
//    connect(m_controller,&SP_Controller::notifyPainterState,[=](QColor color){
//        m_color = color;
//    });



}

SP_Model::~SP_Model()
{

}

void SP_Model::setController(SP_Controller *ctr)
{
    m_controller = ctr;

    connect(this,&SP_Model::UnTodoEvent,m_controller,&SP_Controller::UnTodoEventHandler);
    connect(m_controller,&SP_Controller::undosigal,this,&SP_Model::undo);
}

//开始收集点
void SP_Model::onBeginColloctPoint(int x, int y)
{
    if(m_points.empty()){
        m_points.append(QPoint(x,y));
    }else{
        //TODO::error 处理
    }
}

//结束收集点过程
void SP_Model::onEndColloctPoint(int x, int y)
{
    if(m_points.empty()){
        //TODO::error 处理
    }else{
        m_points.clear();
        ActionData a(m_points,m_color);
        m_UndoStack.push(a);
    }
}

//收集点过程
void SP_Model::onColloctPoint(int x, int y)
{
    if(m_points.empty()){
        //TODO::error 处理
    }else{
        m_points.append(QPoint(x,y));
    }
}

void SP_Model::undo(int times)
{
    qDebug()<<"SP_Controller::undo() ccccccccccccccccc";
    Q_UNUSED(times)

    if(m_UndoStack.empty()){
        return;
    }
    ActionData temp = m_UndoStack.pop();
    m_TodoStack.push(temp);

    emit UnTodoEvent(temp.points);
}



