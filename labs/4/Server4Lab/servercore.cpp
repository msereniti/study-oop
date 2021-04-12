#include "servercore.h"

#include "polinom.h"

#include <sstream>
#include <cstring>

ServerCore::ServerCore(QObject *parent) : QObject(parent)
{
    ConnectionInfo info;

    info.bindAddres = QHostAddress("127.0.0.1");
    info.bindPort = 10001;
    info.sendAddres = QHostAddress("127.0.0.1");
    info.sendPort = 10000;

    _connection = new ServerConnection(this, info);
    _calculator = new Polinom();

    connect(_connection, &ServerConnection::sigReceivedRequest,
            this, &ServerCore::handleOnNewCalculation);
}

void ServerCore::handleOnNewCalculation(Request req)
{
    _calculator->setA(req.aCoef);
    _calculator->setB(req.bCoef);
    _calculator->setC(req.cCoef);
    _calculator->resolve(req.xVarible);

    PolynomialRoots roots = _calculator->getRoots();
    QStringList answer;

    if (roots.NaN)
    {
        answer.append("Polynomial has no integer roots");
    }
    else
    {
        std::stringstream rootsStream;
        std::string rootsOutput = "";
        rootsStream << "" << roots.minor << "," << roots.major << " \0";
        rootsStream >> rootsOutput;

        answer.append(QString::fromUtf8(rootsOutput.c_str()));
    }

    std::stringstream valueStream;
    std::string valueOutput = "";
    valueStream << _calculator->resolve(req.xVarible);
    valueStream >> valueOutput;

    answer.append(QString::fromUtf8(valueOutput.c_str()));
    answer.append(QString::fromUtf8(_calculator->toString().c_str()));
    answer.append(QString::fromUtf8(_calculator->toStringCanonical().c_str()));

    _connection->send(answer);
}
