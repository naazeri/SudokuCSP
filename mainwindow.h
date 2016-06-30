#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QTimer>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QList<QLabel*> *labelList;

private slots:
    void on_pushButton_clicked();
    void setEffects();

private:
    Ui::MainWindow *ui;
    void setupTimer();
    QTimer dataTimer;
};

#endif // MAINWINDOW_H
