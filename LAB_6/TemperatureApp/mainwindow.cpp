#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTime>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , temperature(0.0)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateValues);
    timer->start(1000); // Каждую секунду
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updateValues() {
    temperature = QRandomGenerator::global()->bounded(1, 101); // Случайное значение от 1 до 100
    QString currentTime = QTime::currentTime().toString(); // Получение текущего времени
    ui->temperatureLabel->setText(QString::number(temperature));
    ui->timeLabel->setText(currentTime);
    qDebug() << "Current temperature:" << temperature;
    qDebug() << "Current time:" << currentTime;
}
