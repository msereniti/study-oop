#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H

#include <QObject>
#include <QHostAddress>

struct Request
{
    int aCoef = 0;
    int bCoef = 0;
    int cCoef = 0;
    int xVarible = 0;
};

struct ConnectionInfo
{
    QHostAddress bindAddres = QHostAddress();
    qint16 bindPort = 0;
    QHostAddress sendAddres = QHostAddress();
    qint16 sendPort = 0;
};

class QUdpSocket;
class ClientConnection : public QObject
{
    Q_OBJECT
public:
    explicit ClientConnection(QObject *parent = nullptr,
                              const ConnectionInfo &info = ConnectionInfo());

    void send(Request req);

signals:
    void sigReceivedAnswer(QStringList results);

private slots:
    void handleOnReadyRead();

private:
    QUdpSocket *_connection;

    QHostAddress _sendAddr;
    qint16 _sendPort = 0;

};

#endif // CLIENTCONNECTION_H
