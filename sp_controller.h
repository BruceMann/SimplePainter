#ifndef SPController_H
#define SPController_H

#include <QObject>
#include <QColor>
#include <QPoint>
#include <QList>

class SPModel;

//class painterStates:public QObject
//{
//    Q_OBJECT
//public:
//    QColor m_color;        //记录画笔颜色
//    int m_pixSize;         //线宽像素大小
//};

class SPController:public QObject
{
    Q_OBJECT


public:
    explicit SPController(QObject* parent=nullptr);

    ~SPController();

public slots:
    Q_INVOKABLE void onMousePressed(int x,int y);
    Q_INVOKABLE void onMouseRelesed(int x,int y);
    Q_INVOKABLE void onMousePositionChanged(int x,int y);
    Q_INVOKABLE void onColorChange(QColor color);

    Q_INVOKABLE void undo();
    void UnTodoEventHandler(QList<QPoint>& data);

signals:
    void beginCollectPoint(int x,int y);
    void collectPoint(int x,int y);
    void endCollectPoint(int x,int y);

    void sendData(int mouseAct,int x,int y);

    void notifyPainterState(QColor color);

    void undosigal();

private:
    int m_mouseAction;     //记录鼠标操作，暂时用int  0:pressed 1:relesed 2:holdon

    QColor m_color;        //记录画笔颜色
    //int m_pixSize;         //线宽像素大小
    SPModel *m_model;
};

#endif // SPController_H
