#ifndef STATEWINDOW_H
#define STATEWINDOW_H

#include <QCloseEvent>
#include <QLabel>
#include <QTextEdit>
#include <QWidget>

#include "statedata.h"

class TStateWindow : public QWidget {
  Q_OBJECT

  QLabel *timePassedLabel;
  QLabel *timePassedValueLabel;
  QLabel *rejectedPassengersLabel;
  QLabel *rejectedPassengersValueLabel;
  QLabel *beforeQueueLabel;
  QLabel *beforeQueueValueLabel;
  QLabel *queueLabel;
  QTextEdit *queueTextEdit;

public:
  TStateWindow(QWidget *parent = 0);
  ~TStateWindow();

  void setCurrentState(const TStateData);

protected:
  void closeEvent(QCloseEvent *);

signals:
  void closing();
};

#endif // STATEWINDOW_H
