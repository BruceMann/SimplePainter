#ifndef SPController_H
#define SPController_H

#include <QObject>
#include <QColor>
#include <QPoint>
#include <QList>

#include "define.h"

class SPModel;
class PaintedItem;

class SPController:public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool modelData READ modelData WRITE setModelData NOTIFY modelDataChanged)

public:
    explicit SPController(QObject* parent=nullptr);

    ~SPController();

    void setView(PaintedItem* view);

    bool modelData();
    void setModelData(bool flag);

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

signals:
    void beginCollectPoint(int x,int y);
    void collectPoint(int x,int y);
    void endCollectPoint(int x,int y);

    void sendData(int mouseAct,int x,int y);

    void notifyPainterState(QColor color);

    void undosigal();

    void modelDataChanged();

private:
    int m_mouseAction;     //记录鼠标操作，暂时用int  0:pressed 1:relesed 2:holdon

    QColor m_color;        //记录画笔颜色
    //int m_pixSize;         //线宽像素大小
    SPModel *m_model;
    PaintedItem *m_view;

    bool m_modelData;
};

#endif // SPController_H
