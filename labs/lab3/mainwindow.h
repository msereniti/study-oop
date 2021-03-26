#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void updateUi();

private slots:
  void on_pushButton_clicked();

  void on_doubleSpinBox_valueChanged(double arg1);

  void on_doubleSpinBox_2_valueChanged(double arg1);

  void on_doubleSpinBox_3_valueChanged(double arg1);

  void on_doubleSpinBox_4_valueChanged(double arg1);

private:
  Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
