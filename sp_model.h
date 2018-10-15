#ifndef SP_MODEL_H
#define SP_MODEL_H

#include <QObject>
#include <QColor>
#include <QList>
#include <QStack>
#include <QPoint>

typedef QList<QPoint> PointsList;

class SP_Model:public QObject
{
    Q_OBJECT
public:
    explicit SP_Model(QObject *parent = nullptr);
    ~SP_Model();


private:
    QColor m_color;
    PointsList m_points;             //画一笔的点集合
    QStack<PointsList> m_UndoStack;  //Undo操作栈
    QStack<PointsList> m_TodoStack;  //Redo操作栈
};

#endif // SP_MODEL_H
