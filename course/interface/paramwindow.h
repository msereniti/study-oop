#ifndef PARAMWINDOW_H
#define PARAMWINDOW_H

#include <QCloseEvent>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QWidget>

#include "paramdata.h"

class TParamWindow : public QWidget {
  Q_OBJECT

  QLabel *l1;
  QLabel *l2;
  QLabel *l3;
  QSpinBox *slotsCount_n;
  QSpinBox *maxQueue_m;
  QSpinBox *handlingTime;
  QPushButton *b;
  QPushButton *r;

public:
  TParamWindow(bool, QWidget *parent = 0);
  ~TParamWindow();

  inline void setEnable(const bool m) { setEnabled(m); }
  void setCurrentParams(const TParamData);

protected:
  void closeEvent(QCloseEvent *);

protected slots:
  void setModelParam();

signals:
  void closing();
  void sendModelParams(TParamData);
  void restoryParams();
};

#endif // PARAMWINDOW_H
