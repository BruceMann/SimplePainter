#include "sp_model.h"
#include <QDebug>

SPModel::SPModel(QObject *parent)
    :QObject(parent)
{

}

SPModel::~SPModel()
{

}

const Strokes &SPModel::getStrokes()
{
    qDebug()<<"const Strokes &SPModel::getStrokes()"<<m_stokeVec.size();
    foreach (Stroke* iter, m_stokeVec) {
       qDebug()<<"iter.points.size()"<<iter->points.size();
    }
    return m_stokeVec;
}

void SPModel::onBeginColloctPoint(int x, int y)
{
    qDebug()<<"onBeginColloctPoint"<<x<<" "<<y;
    m_stroke = new Stroke;
    //qDebug()<<"onBeginColloctPoint  before m_stokeVec.size() :"<<m_stokeVec.size();
    m_stokeVec.push_back(m_stroke);
    qDebug()<<"onBeginColloctPoint   m_stokeVec.size() :"<<m_stokeVec.size();
    m_stroke->points.append(QPoint(x,y));
    m_stroke->states = m_color;
    emit pointDataChanged();
}

void SPModel::onEndColloctPoint(int x, int y)
{

    if(m_stroke->points.empty()){
        //TODO::error 处理
    }else{

        qDebug()<<"onEndColloctPoint   m_stokeVec.size() :"<<m_stokeVec.size();
        //qDebug()<<"onEndColloctPoint   Points num:"<<points.size();
        //m_UndoStack.push(*m_stroke);
        emit pointDataChanged();
    }
}

void SPModel::onColloctPoint(int x, int y)
{

    if(m_stroke->points.empty()){
        //TODO::error 处理
    }else{
        //qDebug()<<"onColloctPoint"<<x<<" "<<y;
        m_stroke->points.append(QPoint(x,y));
        emit pointDataChanged();
    }
}

void SPModel::undo()
{
//    if(m_UndoStack.empty()){
//        return;
//    }
//    ActionData temp = m_UndoStack.top();
//    m_TodoStack.push(temp);
//    m_UndoStack.pop();

    //emit UnTodoEvent(temp.points);
}



