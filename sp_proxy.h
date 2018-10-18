#ifndef SP_PROXY_H
#define SP_PROXY_H

#include <QObject>
#include <QColor>
#include <QtNetwork>
#include <QUuid>

class SPProxy:public QObject
{
    Q_OBJECT
public:
    explicit SPProxy(QObject *parent = nullptr);
    ~SPProxy();

    void ConnectToServer();

    void undo(const QUuid& id);
    void clear(const QUuid& id);

public slots:
    void sendStatesData(QColor state);
    void sendDatagram(QUuid id,int mouseAct,int x,int y);
    void processPendingDatagrams();

signals:
    void reciveDatagrams(QUuid id,int mouseAct,float x,float y);
    void statesChange(QColor states);
    void undoEvent(QUuid uid);
    void clearEvent(QUuid uid);

private:
    QUdpSocket *udpSocket = nullptr;

};

#endif // SP_PROXY_H
