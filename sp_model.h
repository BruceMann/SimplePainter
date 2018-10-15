#ifndef SP_MODEL_H
#define SP_MODEL_H

#include <QObject>
#include <QColor>
#include <QList>
#include <QStack>
#include <QPoint>

class SP_Controller;

typedef QList<QPoint> PointsList;

class ActionData    //一个操作的数据结构
{
   public:
    ActionData(){}

    ActionData(PointsList p,QColor c){
        points = p;
        states = c;
    }
    PointsList points;
    QColor states;
};



class SP_Model:public QObject
{
    Q_OBJECT
public:
    explicit SP_Model(QObject *parent = nullptr);
    ~SP_Model();

    void setController(SP_Controller* ctr);

public slots:
    void onBeginColloctPoint(int x,int y);
    void onEndColloctPoint(int x,int y);
    void onColloctPoint(int x,int y);

    void undo(int times=1);    //undo操作，@param times 撤销次数 默认一次TODO::目前只处理一次

signals:
    void UnTodoEvent(QList<QPoint> &points);

private:
    QColor m_color;  //TODO 此处要改为painterState数据结构，以记录其他绘画状态
    PointsList m_points;             //画一笔的点集合
    QStack<ActionData> m_UndoStack;  //Undo操作栈
    QStack<ActionData> m_TodoStack;  //Redo操作栈

    SP_Controller *m_controller;
};

#endif // SP_MODEL_H
