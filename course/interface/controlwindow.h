#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H

#include <QCloseEvent>
#include <QPushButton>
#include <QWidget>

class TControlWindow : public QWidget {
  Q_OBJECT

  QPushButton *resetBtn;
  QPushButton *nextStepBtn;
  QPushButton *addPassengerBtn;
  QPushButton *realTimeBtn;

public:
  TControlWindow(bool, QWidget *parent = 0);
  ~TControlWindow();

  inline void setEnable(const bool realTimeMode) { setEnabled(realTimeMode); }

protected:
  void closeEvent(QCloseEvent *);

private slots:
  void switchMode();

signals:
  void closing();
  void reset();
  void step();
  void addPassenger();
  void mode(bool);
};

#endif // CONTROLWINDOW_H
