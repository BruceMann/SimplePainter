#ifndef DEFINE_H
#define DEFINE_H

#include <QList>
#include <QStack>
#include <QPoint>
#include <QVector>

#include "z_math.h"

typedef QList<QPoint> PointsList;


class Stroke    //一个操作的数据结构
{
   public:
    Stroke(){
        //points = QList<QPoint>();
        arr = z_new_fpoint_array(50, 5);
    }

//    Stroke(PointsList p,QColor c){
//        points = p;
//        states = c;
//    }

    void clear(){
//        points.clear();
        z_drop_fpoint_array(arr);
    }

//    PointsList points;
    z_fpoint_array *arr;
    QColor states;
};

typedef QVector<Stroke*> Strokes;


#endif // DEFINE_H
