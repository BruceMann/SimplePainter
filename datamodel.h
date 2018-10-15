#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QObject>
#include <QList>
#include <QtQml>
#include <QColor>


QT_BEGIN_NAMESPACE
class QUdpSocket;
QT_END_NAMESPACE


class PointData:public QObject{
    Q_OBJECT
    Q_PROPERTY(float posX READ posX WRITE setPosX
               NOTIFY posChanged)
    Q_PROPERTY(float posY READ posY WRITE setPosY
               NOTIFY posChanged)
    Q_PROPERTY(int opera READ opera WRITE setOpera
               NOTIFY operaChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor)


public:
    explicit PointData(QObject *parent = 0);
    PointData(const PointData &other);

    float posX() const;
    float posY() const;
    int   opera() const;
    QColor color() const;

    void setPosX(const float x);
    void setPosY(const float y);
    void setOpera(const int op);
    void setColor(const QColor cl);

signals:
    void posChanged();
    void operaChanged();

private:
    float m_x;
    float m_y;
    QColor m_color;
    int m_pixSize;
    int m_opera;  //操作标志：0 ：按下  1：释放 2：holdon
};

Q_DECLARE_METATYPE(PointData)


class DataModel:public QObject
{
    Q_OBJECT

    Q_PROPERTY(PointData *pointData READ pointData
               NOTIFY pointDataChanged)

public:
    explicit DataModel(QObject* parent = nullptr);
    ~DataModel();

    void ConnectToServer();

    PointData *pointData() const;

public slots:
    Q_INVOKABLE void broadcastDatagram(float x,float y,int opera,QColor color);
    void processPendingDatagrams();

signals:
    void pointDataChanged();

private:
    QUdpSocket *udpSocket = nullptr;
    PointData *m_pointData;
};

#endif // DATAMODEL_H
