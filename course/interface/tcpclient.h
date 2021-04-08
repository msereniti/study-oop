#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QByteArray>
#include <QTcpSocket>
#include <QHostAddress>

class TTcpClient : public QTcpSocket
{
    Q_OBJECT
    bool connected;
public:
    TTcpClient(QHostAddress,quint16);
private slots:
    void connection();
    void disconnection();
    void reading();
public slots:
    void send(QByteArray);
signals:
    void recieve(QByteArray);
};

#endif // TCPCLIENT_H
