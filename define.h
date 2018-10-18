#ifndef DEFINE_H
#define DEFINE_H

#include <QList>
#include <QStack>
#include <QPoint>
#include <QVector>
#include <QUuid>

#include "z_math.h"

typedef QList<QPoint> PointsList;

class Stroke    //一个操作的数据结构
{
   public:
    Stroke(){
        arr = z_new_fpoint_array(50, 5);
    }

    void clear(){
        z_drop_fpoint_array(arr);
    }

    z_fpoint_array *arr;
    QColor states;
    QUuid ownerID;
};

typedef QVector<Stroke*> Strokes;


#endif // DEFINE_H
