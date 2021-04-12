#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include <QObject>
#include <QHostAddress>

struct ConnectionInfo
{
    QHostAddress bindAddres = QHostAddress();
    qint16 bindPort = 0;
    QHostAddress sendAddres = QHostAddress();
    qint16 sendPort = 0;
};

struct Request
{
    int aCoef = 0;
    int bCoef = 0;
    int cCoef = 0;
    int xVarible = 0;
};

class QUdpSocket;
class ServerConnection : public QObject
{
    Q_OBJECT
public:
    explicit ServerConnection(QObject *parent = nullptr,
                              const ConnectionInfo &info = ConnectionInfo());

    void send(QStringList ans);

signals:
    void sigReceivedRequest(Request results);

private slots:
    void handleOnReadyRead();

private:
    QUdpSocket *_connection;

    QHostAddress _sendAddr;
    qint16 _sendPort = 0;

};

#endif // SERVERCONNECTION_H
