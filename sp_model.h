#ifndef SPModel_H
#define SPModel_H

#include <QObject>
#include <QColor>
#include <QList>
#include <QStack>
#include <QPoint>

class SPController;

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



class SPModel:public QObject
{
    Q_OBJECT
public:
    explicit SPModel(QObject *parent = nullptr);
    SPModel(QObject *parent, SPController *ctr);
    ~SPModel();

    void setController(SPController* ctr);

public slots:
    void onBeginColloctPoint(int x,int y);
    void onEndColloctPoint(int x,int y);
    void onColloctPoint(int x,int y);

    void undo();    //undo操作，@param times 撤销次数 默认一次TODO::目前只处理一次

signals:
    void UnTodoEvent(PointsList& points);

private:
    QColor m_color;  //TODO 此处要改为painterState数据结构，以记录其他绘画状态
    PointsList m_points;             //画一笔的点集合
    QStack<ActionData> m_UndoStack;  //Undo操作栈
    QStack<ActionData> m_TodoStack;  //Redo操作栈

    SPController *m_controller;
};

#endif // SPModel_H
