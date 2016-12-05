#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QAudioInput>
#include <QAudioDecoder>
#include <QAudioFormat>
#include <math.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , audioPlayer(this)
    , sound(parent)
{
    ui->setupUi(this);
    initializeAudio();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::initializeAudio(){
    //on_frequencySlider_valueChanged(ui->frequencySlider->value());
    //on_gainSlider_valueChanged(ui->gainSlider->value());

    //audioPlayer.setAudioSource(&oscillatorSource);
    //audioPlayer.start();

    sound.init();
}


void MainWindow::on_frequencySlider_valueChanged(int value)
{
    // 0 ... 100% --> 100Hz ... 10000Hz
    float scaledValue = 2 * value / 100.f + 2;
    float frequency = pow(10, scaledValue);

    ui->frequencyLabel->setText(QString::number((int)frequency));
    oscillatorSource.setFrequency(frequency);
}

void MainWindow::on_waveformCombobox_activated(int index)
{
    oscillatorSource.setSelectedOscillator(index);
}

void MainWindow::on_gainSlider_valueChanged(int value)
{
    oscillatorSource.setGain(value);
}

