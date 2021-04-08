#ifndef APPLICATION_H
#define APPLICATION_H

#include <QCoreApplication>
#include "tcpserver.h"
#include "model.h"
#include "eventtypes.h"

class TApplication : public QCoreApplication
{
    Q_OBJECT
    TTcpServer* server;
    TModel *model;
    bool formMessage(QByteArray&,EEvents,void*);
public:
    TApplication(int,char**);
    ~TApplication();
public slots:
    void clientno(int);
    void clientRequest(int,QByteArray);
};

#endif // APPLICATION_H
