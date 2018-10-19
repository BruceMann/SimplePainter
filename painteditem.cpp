#include "painteditem.h"

#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QColor>

#include <QDebug>
#include "sp_controller.h"

#include "define.h"

extern SPController *controller;

PaintedItem::PaintedItem(QQuickItem *parent)
    : QQuickPaintedItem(parent)
    , m_pen(Qt::red)
{
    //setAcceptedMouseButtons(Qt::LeftButton);
    qDebug()<<"PaintedItem::PaintedItem(QQuickItem *parent)";
    //controller->setView(this);
    m_Stroke = nullptr;
}

PaintedItem::~PaintedItem()
{
    //purgePaintElements();
}

void PaintedItem::setStroke(Stroke *stroke)
{
    //qDebug()<<"void PaintedItem::setStrokes(Strokes *strokes)"<<strokes.size();
    m_Stroke = stroke;
    update();
}

void PaintedItem::paint(QPainter *painter)
{
    if(m_Stroke == nullptr)
        return;

    painter->setRenderHint(QPainter::Antialiasing);

    int point_num = m_Stroke->arr->point.size();
    for(int i=1; i<point_num; i++) {
        m_pen.setColor(m_Stroke->states);
        m_pen.setWidth(5*m_Stroke->arr->point[i].w);
        painter->setPen(m_pen);
        painter->drawLine(QPointF( m_Stroke->arr->point[i-1].p.x,  m_Stroke->arr->point[i-1].p.y), QPointF( m_Stroke->arr->point[i].p.x,  m_Stroke->arr->point[i].p.y));
    }
}


