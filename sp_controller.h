#ifndef SPController_H
#define SPController_H

#include <QObject>
#include <QColor>
#include <QPoint>
#include <QList>

#include "define.h"

class SPModel;
class PaintedItem;
class SPProxy;

class SPController:public QObject
{
    Q_OBJECT

public:
    explicit SPController(QObject* parent=nullptr);

    ~SPController();

    void setView(PaintedItem* view);

private:
    void updateView();
    const Strokes& getStrokes();

public slots:
    Q_INVOKABLE void onMousePressed(int x,int y);
    Q_INVOKABLE void onMouseRelesed(int x,int y);
    Q_INVOKABLE void onMousePositionChanged(int x,int y);
    Q_INVOKABLE void onColorChange(QColor color);

    Q_INVOKABLE void undo();
    Q_INVOKABLE void clear();

    void onPointDataChanged();
    void onReceiveDatagrams(QUuid id, int mouseAct, float x, float y);
    void onOtherUndo(QUuid otherId);
    void onOtherClear(QUuid otherId);

signals:
    void beginCollectPoint(int x,int y);
    void collectPoint(int x,int y);
    void endCollectPoint(int x,int y);

    void sendData(int mouseAct,int x,int y);

    void notifyPainterState(QColor color);

private:
    int m_mouseAction;     //记录鼠标操作，暂时用int  0:pressed 1:relesed 2:holdon

    QColor m_color;        //记录画笔颜色
    //int m_pixSize;         //线宽像素大小
    SPModel *m_model;
    PaintedItem *m_view;
    SPProxy *m_proxy;
};

#endif // SPController_H
