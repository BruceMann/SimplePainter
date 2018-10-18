#include "sp_model.h"
#include <QDebug>

SPModel::SPModel(QObject *parent)
    :QObject(parent)
{
    m_userID = QUuid::createUuid();
    qDebug()<<"my userID is: "<<m_userID;
}

SPModel::~SPModel()
{

}

const Strokes &SPModel::getStrokes()
{
    qDebug()<<"const Strokes &SPModel::getStrokes()"<<m_stokeVec.size();
    return m_stokeVec;
}

void SPModel::setStates(const QColor state)
{
    m_color = state;
}

const QUuid &SPModel::getUserId()
{
    return m_userID;
}

void SPModel::onBeginColloctPoint(QUuid id, int x, int y)
{
    m_stroke = new Stroke;
    m_stroke->ownerID = id;
    m_stokeVec.append(m_stroke);

    z_insert_point(m_stroke->arr,{(float)x, (float)y});
    m_stroke->states = m_color;
    emit pointDataChanged();
}

void SPModel::onEndColloctPoint(int x, int y)
{
    z_insert_last_point(m_stroke->arr, {(float)x, (float)y});
    m_UndoStack.push(*m_stroke);
    emit pointDataChanged();
}

void SPModel::onColloctPoint(int x, int y)
{
    z_insert_point(m_stroke->arr,{(float)x, (float)y});
    emit pointDataChanged();
}

void SPModel::undo(QUuid uid)
{   
    qDebug()<<"void SPModel::undo(QUuid uid)"<<uid;
    if(m_stokeVec.empty()){
        return;
    }
    for(QVector<Stroke*>::reverse_iterator iter=m_stokeVec.rbegin();iter!=m_stokeVec.rend();++iter)
    {

//        if(m_stokeVec.takeLast()->ownerID==uid)

        if(((*iter)->ownerID)==uid)
        {
            m_stokeVec.erase(&(*iter));
            break;
        }
    }
    //m_stokeVec.takeLast();
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



