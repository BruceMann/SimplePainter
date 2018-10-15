#ifndef SP_CONTROLLER_H
#define SP_CONTROLLER_H

#include <QObject>
#include <QColor>

//class painterStates:public QObject
//{
//    Q_OBJECT
//public:
//    QColor m_color;        //记录画笔颜色
//    int m_pixSize;         //线宽像素大小
//};

class SP_Controller:public QObject
{
    Q_OBJECT
public:
    explicit SP_Controller(QObject* parent=nullptr);
    ~SP_Controller();

public slots:
    Q_INVOKABLE void onMousePressed(int x,int y);
    Q_INVOKABLE void onMouseRelesed(int x,int y);
    Q_INVOKABLE void onMousePositionChanged(int x,int y);
    Q_INVOKABLE void onColorChange(QColor color);

signals:
    void beginCollectPoint(int x,int y);
    void collectPoint(int x,int y);
    void endColllectPoint();

    void sendData(int mouseAct,int x,int y);

    void notifyPainterState(QColor color);

private:
    int m_mouseAction;     //记录鼠标操作，暂时用int  0:pressed 1:relesed 2:holdon

    QColor m_color;        //记录画笔颜色
    //int m_pixSize;         //线宽像素大小

};

#endif // SP_CONTROLLER_H