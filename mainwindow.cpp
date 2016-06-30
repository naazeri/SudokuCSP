#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsEffect>
#include <QPropertyAnimation>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    labelList = new QList<QLabel*>();
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            QLabel *label = new QLabel("0", this);
            ui->gridLayout->addWidget(label, i, j, Qt::AlignCenter);
            labelList->append(label);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupTimer()
{
    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(setEffects()));
    dataTimer.start(50); // Interval 0 means to refresh as fast as possible
}

void MainWindow::on_pushButton_clicked()
{
    setupTimer();
}

void MainWindow::setEffects()
{
    static int index = 0;
//    qDebug() << "index:" << index;
    if (index >= 81) {
        dataTimer.stop();
        return;
    }

    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
    labelList->at(index++)->setGraphicsEffect(eff);

    QPropertyAnimation *a = new QPropertyAnimation(eff,"opacity"); // set parent this
    a->setDuration(400);
    a->setStartValue(0);
    a->setEndValue(1);
    a->setEasingCurve(QEasingCurve::InBack);
    a->start(QPropertyAnimation::DeleteWhenStopped);
//        QThread::msleep(100);
}
