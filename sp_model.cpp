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
       //qDebug()<<"iter.points.size()"<<iter->points.size();
    }
    return m_stokeVec;
}

void SPModel::setStates(const QColor state)
{
    m_color = state;
}

void SPModel::onBeginColloctPoint(int x, int y)
{
    qDebug()<<"onBeginColloctPoint"<<x<<" "<<y;
    m_stroke = new Stroke;
    //qDebug()<<"onBeginColloctPoint  before m_stokeVec.size() :"<<m_stokeVec.size();
    m_stokeVec.append(m_stroke);
    qDebug()<<"onBeginColloctPoint   m_stokeVec.size() :"<<m_stokeVec.size();
    //m_stroke->points.append(QPoint(x,y));
    z_insert_point(m_stroke->arr,{(float)x, (float)y});
    m_stroke->states = m_color;
    emit pointDataChanged();
}

void SPModel::onEndColloctPoint(int x, int y)
{
    //if(m_stroke->points.empty()){
        //TODO::error 处理
    //}else{
        qDebug()<<"onEndColloctPoint   m_stokeVec.size() :"<<m_stokeVec.size();
        //qDebug()<<"onEndColloctPoint   Points num:"<<points.size();
        z_insert_last_point(m_stroke->arr, {(float)x, (float)y});
        m_UndoStack.push(*m_stroke);
        emit pointDataChanged();
    //}
}

void SPModel::onColloctPoint(int x, int y)
{
   // if(m_stroke->points.empty()){
        //TODO::error 处理
    //}else{
        //qDebug()<<"onColloctPoint"<<x<<" "<<y;
        //m_stroke->points.append(QPoint(x,y));
        z_insert_point(m_stroke->arr,{(float)x, (float)y});
        emit pointDataChanged();
   // }
}

void SPModel::undo()
{
    if(m_stokeVec.empty()){
        return;
    }
    m_stokeVec.takeLast();
    emit pointDataChanged();
}

void SPModel::clear()
{
    int size = m_stokeVec.size();
    if(size > 0)
    {
        for(int i = 0; i < size; ++i)
        {
            delete m_stokeVec.at(i);
        }
        m_stokeVec.clear();
        m_stroke = nullptr;
        emit pointDataChanged();
    }

}



