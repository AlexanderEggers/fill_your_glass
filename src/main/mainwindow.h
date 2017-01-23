#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QWidget"
#include "QStackedWidget"
#include "soundsystem.h"
#include "facedetection.h"
#include "QThread"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static int const EXIT_CODE_REBOOT;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void showNextScreen();
    void quitGame();
    void restartGame();
    void playGameSound();
    void showDetectionScreen();
public slots:
    void startPlayerInput();
    void updatePlayerInput();
    void endPlayerInput();
private:
    void initGame();
    QWidget* initStartScreen();
    QWidget* initIntructionScreen();
    QWidget* initPlayerReadyScreen();
    QWidget* initGameScreen(int player);
    QWidget* initResultScreen();
private:
    int source;
    double player1Input, player2Input;
    int currentPlayer;

    QStackedWidget *stackedWidget;
    Ui::MainWindow *ui;

    QThread soundThread, faceDetectionThread;

    SoundSystem sound;
    FaceDetection faceDetection;
};

#endif // MAINWINDOW_H
