#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QRandomGenerator> // Добавлено для генерации случайных чисел

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateValues();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    double temperature; // Переменная для хранения температуры
};

#endif // MAINWINDOW_H
