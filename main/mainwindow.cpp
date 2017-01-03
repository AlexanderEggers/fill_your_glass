#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QAudioInput>
#include <QAudioDecoder>
#include <QAudioFormat>
#include <math.h>
#include "game/game.h"
#include "facedetection/facedetection.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , audioPlayer(this)
    , sound(parent)
    , faceDetection()
{
    ui->setupUi(this);
    initialize();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::initialize(){


}

void MainWindow::on_faceBtn_clicked()
{
    faceDetection.detectFaces();
}

void MainWindow::on_audioBtn_clicked()
{
    sound.init();
}

void MainWindow::on_playBtn_clicked()
{
    Game *g = new Game();
    g->show();

}
