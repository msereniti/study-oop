#include "application.h"
#include "eventtypes.h"

TApplication::TApplication(int argc, char **argv) : QApplication(argc, argv) {
  client = new TTcpClient(QHostAddress(QString("127.0.0.1")), 10000);
  connect(client, SIGNAL(recieve(QByteArray)), this,
          SLOT(fromModel(QByteArray)));
  interface = new TInterface();
  connect(interface, SIGNAL(sendModelParams(TParamData)), this,
          SLOT(sendModelParams(TParamData)));
  connect(interface, SIGNAL(paramRequest(EEvents, void *)), this,
          SLOT(toModel(EEvents, void *)));
  connect(interface, SIGNAL(stateRequest(EEvents, void *)), this,
          SLOT(toModel(EEvents, void *)));
  connect(interface, SIGNAL(reset()), this, SLOT(reset()));
  connect(interface, SIGNAL(step()), this, SLOT(step()));
  connect(interface, SIGNAL(addPassenger()), this, SLOT(addPassenger()));
  connect(interface, SIGNAL(mode(bool)), this, SLOT(mode(bool)));
  interface->show();
  generator = new TEventGenerator();
  connect(generator, SIGNAL(timeout()), this, SLOT(step()));
}

TApplication::~TApplication() {
  if (generator->isActive())
    generator->stop();
  delete client;
  delete interface;
  delete generator;
}

void TApplication::toModel(EEvents e, void *d) {
  QByteArray msg;
  TEvents msgData;
  size_t msgLen = sizeof(msgData.type);
  msgData.type = e;
  switch (e) {
  case PARAMREQUEST:
  case STATEREQUEST:
  case RESET:
  case ADD_PASSENGER:
  case TACT:
    msg.append(msgLen, ' ');
    memcpy(msg.data(), &msgData, msgLen);
    break;
  case PARAMMESSAGE:
    msgLen += sizeof(TParamData);
    msgData.data.p = *((TParamData *)d);
    msg.append(msgLen, ' ');
    memcpy(msg.data(), &msgData, msgLen);
    break;
  default:
    return;
  }
  client->send(msg);
}

void TApplication::fromModel(QByteArray m) {
  QByteArray msg(m);
  TEvents msgData;
  size_t header = sizeof(msgData.type);
  size_t length;
  while (msg.size() >= header) {
    length = header;
    memcpy(&msgData, msg.data(), header);
    qDebug() << "msg type =" << msgData.type;
    switch (msgData.type) {
    case CLIENTNO:
      length += sizeof(msgData.data.no);
      memcpy(&msgData, msg.data(), length);
      qDebug() << "CLIENTNO" << msgData.data.no;
      interface->setControlState(msgData.data.no == 1);
      break;
    case PARAMMESSAGE:
      length += sizeof(msgData.data.p);
      memcpy(&msgData, msg.data(), length);
      qDebug() << "PARAMMESSAGE";
      interface->setCurrentParams(msgData.data.p);
      break;
    case STATEMESSAGE:
      length += sizeof(msgData.data.s);
      memcpy(&msgData, msg.data(), length);
      qDebug() << "STATEMESSAGE";
      interface->setCurrentState(msgData.data.s);
      break;
    default:
      qDebug() << "unknown message" << msg;
    }
    msg = msg.right(msg.size() - length);
  }
}

void TApplication::sendModelParams(TParamData pd) {
  toModel(PARAMMESSAGE, (void *)(&pd));
}

void TApplication::reset() {
  qDebug() << "reset command";
  toModel(RESET, nullptr);
}

void TApplication::step() {
  qDebug() << "step";
  toModel(TACT, nullptr);
}

void TApplication::addPassenger() {
  qDebug() << "addPassenger";
  toModel(ADD_PASSENGER, nullptr);
}

void TApplication::mode(bool readlTimeMode) {
  qDebug() << "mode" << readlTimeMode;
  if (readlTimeMode)
    generator->start();
  else
    generator->stop();
}
