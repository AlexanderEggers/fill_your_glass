#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QWidget"
#include "QStackedWidget"
#include "QTimer"
#include "QLabel"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void handleButton();
    void updateGUITime();
private:
    QStackedWidget *stackedWidget;
    Ui::MainWindow *ui;
    QWidget* initStartScreen();
    QWidget* initIntructionScreen();
    QWidget* initPlayerReadyScreen(int player);
    QWidget* initGameScreen(int player);

private:
    int source;
    int timeLeft;
    QTimer *qTimer;
    QLabel *guiTime1, *guiTime2;
};

#endif // MAINWINDOW_H
