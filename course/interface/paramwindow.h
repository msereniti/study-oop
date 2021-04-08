#ifndef PARAMWINDOW_H
#define PARAMWINDOW_H

#include <QWidget>
#include <QCloseEvent>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>

#include "paramdata.h"

class TParamWindow : public QWidget
{
Q_OBJECT

    QLabel *l1;
    QLabel *l2;
    QLabel *l3;
    QSpinBox *modulo;
    QSpinBox *param1;
    QSpinBox *param2;
    QPushButton *b;
    QPushButton *r;

public:
    TParamWindow(bool,QWidget *parent = 0);
    ~TParamWindow();

    inline void setEnable(const bool m) { setEnabled(m); }
    void setCurrentParams(const TParamData);

protected:
    void closeEvent(QCloseEvent*);

protected slots:
    void setModelParam();

signals:
    void closing();
    void sendModelParams(TParamData);
    void restoryParams();
};

#endif // PARAMWINDOW_H
