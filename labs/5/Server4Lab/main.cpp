#include <QCoreApplication>
#include <QDebug>

#include "servercore.h"

int main(int argc, char *argv[]) {
  qDebug() << "Start server";
  QCoreApplication a(argc, argv);

  ServerCore core;

  return a.exec();
}
