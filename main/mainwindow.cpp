#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QAudioInput>
#include <QAudioDecoder>
#include <QAudioFormat>
#include <math.h>
#include "game/game.h"
#include "facedetection/facedetection.h"
#include "soundSystem/soundsystem.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , audioPlayer(this)
    , sound(parent)
    , faceDetection()
{
    ui->setupUi(this);
    initialize();
    MainWindow::setWindowTitle("Fill Your Glass");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::initialize(){
    QObject::connect(&faceDetection, SIGNAL(signalMouthOpenEvent(void)),
                        &sound, SLOT(handleMouthOpenEvent(void)));
    QObject::connect(&faceDetection, SIGNAL(signalMouthClosedEvent(void)),
                        &sound, SLOT(handleMouthClosedEvent(void)));
    soundThread.start();
    sound.moveToThread(&soundThread);
}

void MainWindow::on_faceBtn_clicked()
{
    faceDetection.detectFaces();
}

void MainWindow::on_audioBtn_clicked()
{
    //sound.init();
}

void MainWindow::on_playBtn_clicked()
{
    Game *g = new Game();
    g->show();

}
