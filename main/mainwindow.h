#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QAudioOutput>
#include "audioplayer.h"
#include "oscillatorsource.h"
#include "soundsystem.h"
#include "facedetection.h"

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

    void on_faceBtn_clicked();

    void on_audioBtn_clicked();

    void on_playBtn_clicked();

private:
    void initialize();
    Ui::MainWindow *ui;
    AudioPlayer audioPlayer;
    SoundSystem sound;
    FaceDetection faceDetection;
};

#endif // MAINWINDOW_H
