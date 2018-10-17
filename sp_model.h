#ifndef SPModel_H
#define SPModel_H

#include <QObject>
#include <QColor>

#include "define.h"


class SPModel:public QObject
{
    Q_OBJECT
public:
    explicit SPModel(QObject *parent = nullptr);
    ~SPModel();

    const Strokes& getStrokes();
    void setStates(const QColor state);

public slots:
    void onBeginColloctPoint(int x,int y);
    void onEndColloctPoint(int x,int y);
    void onColloctPoint(int x,int y);

    void undo();    //undo操作，@param times 撤销次数 默认一次TODO::目前只处理一次
    void clear();

signals:
    void pointDataChanged();

private:
    QColor m_color;              //TODO 此处要改为painterState数据结构，以记录其他绘画状态
    Stroke *m_stroke;            //画一笔的点集合
    Strokes m_stokeVec;         //所有元素
    QStack<Stroke> m_UndoStack;  //Undo操作栈
    QStack<Stroke> m_TodoStack;  //Redo操作栈
};

#endif // SPModel_H
