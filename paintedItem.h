#ifndef SP_VIEW_H
#define SP_VIEW_H

#include <QQuickPaintedItem>
#include <QVector>
#include <QPoint>
#include <QLine>
#include <QPen>

struct ElementGroup
{
    QVector<QLine> m_lines;
    QPen m_pen;
};

class SPView:public QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit SPView(QQuickItem *parent=nullptr);
    ~SPView();

    void paint(QPainter *painer) override;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void purgePaintElements();

protected:
    QVector<ElementGroup*> m_elements;
    ElementGroup *m_element;   //the current ElementGroup
    QPoint m_lastPoint;
    QPen m_pen;   //the Current Pen
};

#endif // SP_VIEW_H
