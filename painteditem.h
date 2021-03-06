#ifndef PAINTEDITEM_H
#define PAINTEDITEM_H
#include <QQuickPaintedItem>
#include <QVector>
#include <QPointF>
#include <QLineF>
#include <QPen>

#include "define.h"

class PaintedItem : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(QColor penColor READ penColor WRITE setPenColor)

public:
    PaintedItem(QQuickItem *parent = 0);
    ~PaintedItem();

    QColor penColor() const { return m_pen.color(); }
    void setPenColor(QColor color) { m_pen.setColor(color); }

    void setStrokes(const Strokes& strokes);

    void paint(QPainter *painter);

signals:
    void mousePresse(int x,int y);
    void mouseRelease(int x,int y);
    void mouseMove(int x,int y);

protected:
    QPen m_pen; // the Current Pen

private:
    Strokes m_Strokes;
};

#endif // PAINTEDITEM_H
