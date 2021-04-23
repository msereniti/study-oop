#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class ClientConnection;
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateUi();

private slots:
    void on_closeButton_clicked();
    void on_sendToCalculation_clicked();

    void handlOnAnswerReceived(const QStringList &data);

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

private:
    Ui::MainWindow *ui;

    ClientConnection *_connection;
};
#endif // MAINWINDOW_H
