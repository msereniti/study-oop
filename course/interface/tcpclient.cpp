#include "tcpclient.h"

#include <QDebug>

TTcpClient::TTcpClient(QHostAddress host, quint16 port) :
    QTcpSocket()
{
    connected = false;
    connectToHost(host,port);
    connect((QAbstractSocket*)this,SIGNAL(connected()),
            this,SLOT(connection()));
    connect((QAbstractSocket*)this,SIGNAL(disconnected()),
            this,SLOT(disconnection()));
    connect((QAbstractSocket*)this,SIGNAL(readyRead()),
            this,SLOT(reading()));
}

void TTcpClient::connection()
{
    qDebug()<<"connection";
    connected = true;
    //write("***");
}

void TTcpClient::disconnection()
{
    connected = false;
    qDebug()<<"disconnection";
}

void TTcpClient::reading()
{
    QByteArray msg;
    msg = readAll();
    if (connected)
    {
        qDebug()<<"reading"<<msg;
        emit recieve(msg);
    }
}

void TTcpClient::send(QByteArray msg)
{
    if (connected)
    {
        write(msg);
        qDebug()<<"send"<<msg;
    }
}
