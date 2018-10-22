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
    //setRenderTarget(QQuickPaintedItem::FramebufferObject);
    setRenderTarget(QQuickPaintedItem::Image);
    setAcceptedMouseButtons(Qt::LeftButton);
    qDebug()<<"PaintedItem::PaintedItem(QQuickItem *parent)";
    controller->setView(this);
}

PaintedItem::~PaintedItem()
{
    //purgePaintElements();
}

void PaintedItem::setStrokes(const Strokes &strokes)
{
    //qDebug()<<"void PaintedItem::setStrokes(Strokes *strokes)"<<strokes.size();
    m_Strokes = strokes;
    update();
}

void PaintedItem::paint(QPainter *painter)
{
    if(m_Strokes.empty())
        return;

    painter->setRenderHint(QPainter::Antialiasing);

    int size = m_Strokes.size();

    qDebug()<<"void PaintedItem::paint(QPainter *painter)"<<size;

    Stroke* stroke;
    for(int i = 0;i<size;++i){
        stroke = m_Strokes.at(i);

        int point_num = stroke->arr->point.size();
        for(int i=1; i<point_num; i++) {
            m_pen.setColor(stroke->states);
            m_pen.setWidth(5*stroke->arr->point[i].w);
            painter->setPen(m_pen);
            painter->drawLine(QPointF( stroke->arr->point[i-1].p.x,  stroke->arr->point[i-1].p.y), QPointF( stroke->arr->point[i].p.x,  stroke->arr->point[i].p.y));
        }
    }
}


