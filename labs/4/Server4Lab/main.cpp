#include <QCoreApplication>

#include "servercore.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ServerCore core;

    return a.exec();
}
