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
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled)
    Q_PROPERTY(int penWidth READ penWidth WRITE setPenWidth)
    Q_PROPERTY(QColor penColor READ penColor WRITE setPenColor)

public:
    PaintedItem(QQuickItem *parent = 0);
    ~PaintedItem();

    bool isEnabled() const{ return m_bEnabled; }
    void setEnabled(bool enabled){ m_bEnabled = enabled; }

    int penWidth() const { return m_pen.width(); }
    void setPenWidth(int width) { m_pen.setWidth(width); }

    QColor penColor() const { return m_pen.color(); }
    void setPenColor(QColor color) { m_pen.setColor(color); }

    void setStrokes(const Strokes& strokes);
    void updateView();


    void paint(QPainter *painter);

signals:
    void mousePresse(int x,int y);
    void mouseRelease(int x,int y);
    void mouseMove(int x,int y);



protected:
    QPointF m_lastPoint;
    bool m_bEnabled;
    bool m_bPressed;
    bool m_bMoved;
    QPen m_pen; // the Current Pen

private:
    Strokes m_Strokes;
};

#endif // PAINTEDITEM_H
