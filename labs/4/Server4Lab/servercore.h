#ifndef SERVERCORE_H
#define SERVERCORE_H

#include "serverconnection.h"

#include <QObject>

class Polinom;
class ServerCore : public QObject
{
    Q_OBJECT
public:
    explicit ServerCore(QObject *parent = nullptr);

private slots:
    void handleOnNewCalculation(Request req);

private:
    ServerConnection *_connection;

    Polinom *_calculator;
};

#endif // SERVERCORE_H
