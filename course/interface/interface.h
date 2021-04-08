#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QCloseEvent>
#include <QPushButton>

#include "eventtypes.h"

class TParamWindow;
class TStateWindow;
class TControlWindow;

class TInterface : public QWidget
{
    Q_OBJECT

    bool canControl;

    TParamWindow   *paramWindow;
    TStateWindow   *stateWindow;
    TControlWindow *controlWindow;

    QPushButton *pbtn;
    QPushButton *sbtn;
    QPushButton *cbtn;

public:
    TInterface(QWidget *parent = 0);
    ~TInterface();

    void setControlState(const bool);
    void setCurrentParams(const TParamData);
    void setCurrentState(const TStateData);

protected:
    void closeEvent(QCloseEvent*);

public slots:
    void paramWindowClosed();
    void stateWindowClosed();
    void controlWindowClosed();
    void restoryParams();

private slots:
    void openParamWindow();
    void openStateWindow();
    void openControlWindow();
signals:
    void paramRequest(EEvents,void*);
    void stateRequest(EEvents,void*);
    void sendModelParams(TParamData);
    void reset();
    void step();
    void mode(bool);
};

#endif // INTERFACE_H
