#ifndef DEFINE_H
#define DEFINE_H

#include <QList>
#include <QStack>
#include <QPoint>
#include <QVector>

typedef QList<QPoint> PointsList;


class Stroke    //一个操作的数据结构
{
   public:
    Stroke(){
        points = QList<QPoint>();
    }

    Stroke(PointsList p,QColor c){
        points = p;
        states = c;
    }

    void clear(){
        points.clear();
    }

    PointsList points;
    QColor states;
};

typedef QVector<Stroke*> Strokes;


#endif // DEFINE_H
