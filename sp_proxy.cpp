#include "sp_proxy.h"

SPProxy::SPProxy(QObject *parent):QObject(parent)
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(55555,QUdpSocket::ShareAddress);

    connect(udpSocket,SIGNAL(readyRead()),this,SLOT(processPendingDatagrams()));

    ConnectToServer();
}

SPProxy::~SPProxy()
{
    qDebug()<<"SPProxy::~SPProxy()";
    QString str ="logout";
    QByteArray loginInfo = str.toLatin1();
    udpSocket->writeDatagram(loginInfo,QHostAddress::LocalHost,44444);
    delete udpSocket;
}

void SPProxy::ConnectToServer()
{
    QString str ="login";
    QByteArray loginInfo = str.toLatin1();
    udpSocket->writeDatagram(loginInfo,QHostAddress::LocalHost,44444);
}

void SPProxy::undo(const QUuid &id)
{
    QString msg = "undo";
    QByteArray datagram = msg.toLatin1()+","+id.toString().toLatin1();
    udpSocket->writeDatagram(datagram,QHostAddress::LocalHost,44444);
}

void SPProxy::clear(const QUuid &id)
{
    QString msg = "clear";
    QByteArray datagram = msg.toLatin1()+","+id.toString().toLatin1();
    udpSocket->writeDatagram(datagram,QHostAddress::LocalHost,44444);
}

void SPProxy::sendStatesData(QColor state)
{
    QString str ="states";
    QByteArray datagram = str.toLatin1()+","+state.name().toLatin1();
    udpSocket->writeDatagram(datagram,QHostAddress::LocalHost,44444);
}

void SPProxy::sendDatagram(QUuid id,int mouseAct, int x, int y)
{
    QByteArray datagram = QByteArray::number(x)+","+QByteArray::number(y)+","+QByteArray::number(mouseAct)+","+id.toString().toLatin1();
    udpSocket->writeDatagram(datagram,QHostAddress::LocalHost,44444);
}

void SPProxy::processPendingDatagrams()
{
    QByteArray datagram;

    while(udpSocket->hasPendingDatagrams()){
        datagram.resize(int(udpSocket->pendingDatagramSize()));
        udpSocket->readDatagram(datagram.data(),datagram.size());
        QString data(datagram.constData());
        QStringList strlist = data.split(',');

        if(QString::compare(strlist[0],"states",Qt::CaseInsensitive)==0){
            qDebug()<<"states change"<<strlist[1];
            emit statesChange(QColor(strlist[1]));
            continue;
        }

        if(QString::compare(strlist[0],"undo",Qt::CaseInsensitive)==0){
            qDebug()<<"undo action"<<strlist[1];
            emit undoEvent(QUuid(strlist[1]));
            continue;
        }

        if(QString::compare(strlist[0],"clear",Qt::CaseInsensitive)==0){
            qDebug()<<"clear action"<<strlist[1];
            emit clearEvent(QUuid(strlist[1]));
            continue;
        }

        float x= strlist[0].toFloat();
        float y= strlist[1].toFloat();
        int mouseAction = strlist[2].toInt();
        QUuid id = QUuid(strlist[3]);

        qDebug()<<"hahhahhaha"<<x<<y<<mouseAction;
        emit reciveDatagrams(id,mouseAction,x,y);
    }
}
