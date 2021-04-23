#include "servercore.h"

#include "polinom.h"

#include <QDebug>
#include <cstring>
#include <sstream>

ServerCore::ServerCore(QObject *parent) : QObject(parent) {
  ConnectionInfo info;

  info.bindAddres = QHostAddress("127.0.0.1");
  info.bindPort = 10001;
  info.sendAddres = QHostAddress("127.0.0.1");
  info.sendPort = 10000;

  _connection = new ServerConnection(this, info);

  connect(_connection, &ServerConnection::sigReceivedRequest, this,
          &ServerCore::handleOnNewCalculation);
}

void ServerCore::handleOnNewCalculation(Request req) {

  char *reqBytes = reinterpret_cast<char *>(&req);

  auto polynomialInt = new Polinom<int>();
  auto polynomialReal = new Polinom<Fract>();

  polynomialInt->setA(req.aCoef);
  polynomialInt->setB(req.bCoef);
  polynomialInt->setC(req.cCoef);
  polynomialInt->resolve(req.xVarible);
  polynomialReal->setA(req.aCoef);
  polynomialReal->setB(req.bCoef);
  polynomialReal->setC(req.cCoef);
  polynomialReal->resolve(req.xVarible);

  PolynomialRoots rootsInt = polynomialInt->getRoots();
  PolynomialRoots rootsReal = polynomialReal->getRoots();
  QStringList answer;

  if (req.mode == 0) {
    if (rootsInt.NaN) {
      answer.append("Polynomial has no integer roots");
    } else {
      std::stringstream rootsStream;
      std::string rootsOutput = "";
      rootsStream << "" << rootsInt.minor << "," << rootsInt.major << " \0";
      rootsStream >> rootsOutput;

      answer.append(QString::fromUtf8(rootsOutput.c_str()));
    }
  } else if (req.mode == 1) {
    if (rootsReal.NaN) {
      answer.append("Polynomial has no integer roots");
    } else {
      std::stringstream rootsStream;
      std::string rootsOutput = "";
      rootsStream << "" << rootsReal.minor << "," << rootsReal.major << " \0";
      rootsStream >> rootsOutput;

      answer.append(QString::fromUtf8(rootsOutput.c_str()));
    }
  }

  std::stringstream valueStream;
  std::string valueOutput = "";
  if (req.mode == 0) {
    valueStream << polynomialInt->resolve(req.xVarible);
  } else if (req.mode == 1) {
    valueStream << polynomialReal->resolve(req.xVarible);
  }
  valueStream >> valueOutput;

  answer.append(QString::fromUtf8(valueOutput.c_str()));
  if (req.mode == 0) {
    answer.append(QString::fromUtf8(polynomialInt->toString().c_str()));
    answer.append(
        QString::fromUtf8(polynomialInt->toStringCanonical().c_str()));
  } else if (req.mode == 1) {
    answer.append(QString::fromUtf8(polynomialReal->toString().c_str()));
    answer.append(
        QString::fromUtf8(polynomialReal->toStringCanonical().c_str()));
  }
  _connection->send(answer);
}
