#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QVBoxLayout"
#include "QHBoxLayout"
#include "QPushButton"
#include "QDebug"
#include <stdlib.h>
#include "facedetection.h"
#include "soundsystem.h"
#include "QThread"
#include "QLabel"

const int STARTSCREEN = 0, INTRODUCTION_SCREEN = 1, PLAYER1_READY_SCREEN = 2,
PLAYER1_GAME_SCREEN = 3, PLAYER2_READY_SCREEN = 4, PLAYER2_GAME_SCREEN = 5, GAME_RESULT_SCREEN = 6;

const int NO_PLAYER = 0, PLAYER1 = 1, PLAYER2 = 2;
const double PLAYER_INPUT_CHANGE_VALUE = 0.02;

int const MainWindow::EXIT_CODE_REBOOT = -123456789;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    sound(new SoundSystem(parent)),
    faceDetection(new FaceDetection(parent))
{
    ui->setupUi(this);
    setWindowTitle("Fill Your Glass");
    setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);
    setFixedHeight(525);
    setFixedWidth(600);

    QObject::connect(&faceDetection, SIGNAL(startMouthEvent(void)),
                            this, SLOT(startPlayerInput(void)));
    QObject::connect(&faceDetection, SIGNAL(updateMouthEvent(void)),
                            this, SLOT(updatePlayerInput(void)));
    QObject::connect(&faceDetection, SIGNAL(endMouthEvent(void)),
                            this, SLOT(endPlayerInput(void)));

    soundThread.start();
    sound.moveToThread(&soundThread);

    stackedWidget = new QStackedWidget;

    initGame();

    QVBoxLayout *box = new QVBoxLayout;
    box->addWidget(stackedWidget);

    QWidget *central = centralWidget();
    central->setLayout(box);
}

void MainWindow::initGame() {
    player1Input = 0;
    player2Input = 0;
    currentPlayer = NO_PLAYER;

    sound.initGameSound();

    if(stackedWidget->count() > 0) {
        source = INTRODUCTION_SCREEN;
        stackedWidget->removeWidget(stackedWidget->widget(GAME_RESULT_SCREEN));
        stackedWidget->setCurrentWidget(stackedWidget->widget(INTRODUCTION_SCREEN));
    } else {
        source = STARTSCREEN;
        stackedWidget->addWidget(initStartScreen());
        stackedWidget->addWidget(initIntructionScreen());
        stackedWidget->addWidget(initPlayerReadyScreen());
        stackedWidget->addWidget(initGameScreen(PLAYER1));
        stackedWidget->addWidget(initPlayerReadyScreen());
        stackedWidget->addWidget(initGameScreen(PLAYER2));
        stackedWidget->setCurrentWidget(stackedWidget->widget(STARTSCREEN));
    }
}

MainWindow::~MainWindow()
{
    soundThread.quit();
    delete ui;
}

QWidget* MainWindow::initStartScreen() {
    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;

    QLabel *label = new QLabel;
    QPixmap image(":/images/startscreen.jpg");
    image = image.scaled(600,400,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    label->setPixmap(image);

    QPushButton *button = new QPushButton("Next");
    connect(button, SIGNAL (released()), this, SLOT (showNextScreen()));

    layout->addWidget(label);
    layout->addWidget(button);

    widget->setLayout(layout);
    return widget;
}

QWidget* MainWindow::initIntructionScreen() {
    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;
    QLabel *label = new QLabel;
    QPixmap image(":/images/intro_Pic.jpg");
    image = image.scaled(600,400,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    label->setPixmap(image);

    QPushButton *button = new QPushButton("Next");
    connect(button, SIGNAL (released()), this, SLOT (showNextScreen()));

    layout->addWidget(label);
    layout->addWidget(button);

    widget->setLayout(layout);
    return widget;
}

QWidget* MainWindow::initPlayerReadyScreen() {
    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;

    QLabel *description = new QLabel;
    QString imageURI = ":/images/player_ready.jpg";
    QPixmap image(imageURI);
    image = image.scaled(600,400,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    description->setPixmap(image);

    QPushButton *readyButton = new QPushButton("Ready");
    connect(readyButton, SIGNAL (released()), this, SLOT (showNextScreen()));

    QPushButton *gameSoundButton = new QPushButton("Play Game Sound");
    connect(gameSoundButton, SIGNAL (released()), this, SLOT (playGameSound()));

    layout->addWidget(description);
    layout->addWidget(readyButton);
    layout->addWidget(gameSoundButton);

    widget->setLayout(layout);
    return widget;
}

QWidget* MainWindow::initGameScreen(int player) {
    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;

    QHBoxLayout *headerLayout = new QHBoxLayout;
    QLabel *playername = new QLabel;

    QLabel *description = new QLabel;
    QString imageURI = "";
    if(player == PLAYER1) {;
        playername->setText("Player 1");
        imageURI = ":/images/player1_game_screen.jpg";
        headerLayout->addWidget(playername);
    } else {
        playername->setText("Player 2");
        imageURI = ":/images/player2_game_screen.jpg";
        headerLayout->addWidget(playername);
    }

    QPixmap image(imageURI);
    image = image.scaled(600,400,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    description->setPixmap(image);

    QPushButton *detectionButton = new QPushButton("Start facial detection");
    connect(detectionButton, SIGNAL (released()), this, SLOT (showDetectionScreen()));

    QPushButton *gameSoundButton = new QPushButton("Play game sound");
    connect(gameSoundButton, SIGNAL (released()), this, SLOT (playGameSound()));

    QPushButton *confirmbutton = new QPushButton("Confirm");
    connect(confirmbutton, SIGNAL (released()), this, SLOT (showNextScreen()));

    QWidget *header = new QWidget;
    header->setLayout(headerLayout);

    layout->addWidget(header);
    layout->addWidget(description);
    layout->addWidget(detectionButton);
    layout->addWidget(gameSoundButton);
    layout->addWidget(confirmbutton);

    widget->setLayout(layout);
    return widget;
}

QWidget* MainWindow::initResultScreen() {
    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;

    QLabel *label = new QLabel;
    QString imageURI = "";
    double soundGameValue = sound.getSoundGameValue();
    double player1InputDiff = abs(soundGameValue - player1Input);
    double player2InputDiff = abs(soundGameValue - player2Input);

    if(player1InputDiff < player2InputDiff) {
        imageURI = ":/images/playerOneWins.jpg";
    } else if(player1InputDiff > player2InputDiff) {
        imageURI = ":/images/playerTwoWins.jpg";
    } else {
        imageURI = ":/images/noPlayerWins.jpg";
    }

    QPixmap image(imageURI);
    image = image.scaled(600,400,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    label->setPixmap(image);

    QPushButton *buttonQuit = new QPushButton("Quit");
    connect(buttonQuit, SIGNAL (released()), this, SLOT (quitGame()));

    QPushButton *buttonRestart = new QPushButton("Restart");
    connect(buttonRestart, SIGNAL (released()), this, SLOT (restartGame()));

    layout->addWidget(label);
    layout->addWidget(buttonQuit);
    layout->addWidget(buttonRestart);

    widget->setLayout(layout);
    return widget;
}


void MainWindow::showNextScreen()
{
    qDebug() << "source old: " << source;

    switch (source) {
        case STARTSCREEN:
            source = INTRODUCTION_SCREEN;
            stackedWidget->setCurrentWidget(stackedWidget->widget(INTRODUCTION_SCREEN));
            break;
        case INTRODUCTION_SCREEN:
            source = PLAYER1_READY_SCREEN;
            stackedWidget->setCurrentWidget(stackedWidget->widget(PLAYER1_READY_SCREEN));
            break;
        case PLAYER1_READY_SCREEN:
            currentPlayer = PLAYER1;
            sound.initPlayerSound();
            source = PLAYER1_GAME_SCREEN;
            stackedWidget->setCurrentWidget(stackedWidget->widget(PLAYER1_GAME_SCREEN));
            break;
        case PLAYER1_GAME_SCREEN:
            currentPlayer = NO_PLAYER;
            source = PLAYER2_READY_SCREEN;
            stackedWidget->setCurrentWidget(stackedWidget->widget(PLAYER2_READY_SCREEN));
            break;
        case PLAYER2_READY_SCREEN:
            currentPlayer = PLAYER2;
            sound.initPlayerSound();
            source = PLAYER2_GAME_SCREEN;
            stackedWidget->setCurrentWidget(stackedWidget->widget(PLAYER2_GAME_SCREEN));
            break;
        case PLAYER2_GAME_SCREEN:
            currentPlayer = NO_PLAYER;
            source = GAME_RESULT_SCREEN;
            stackedWidget->addWidget(initResultScreen());
            stackedWidget->setCurrentWidget(stackedWidget->widget(GAME_RESULT_SCREEN));
            qDebug() << "Player 1: " << player1Input;
            qDebug() << "Player 2: " << player2Input;
            qDebug() << "Sound Game Value: " << sound.getSoundGameValue();
            break;
        default:
            break;
    }

    qDebug() << "source new: " << source;
}

void MainWindow::showDetectionScreen() {
    if(source == PLAYER1_GAME_SCREEN || source == PLAYER2_GAME_SCREEN) {
        qDebug()<< "showDetectionScreen";

        sound.stopGameSound();
        faceDetection.startDetectingFaces();
    }
}

void MainWindow::startPlayerInput() {
    qDebug() << "startPlayerInput";

    if(currentPlayer == PLAYER1 || currentPlayer == PLAYER2) {
        sound.startPlayerSound();
    }
}

void MainWindow::updatePlayerInput() {
    qDebug() << "updatePlayerInput";

    if(currentPlayer == PLAYER1) {
        player1Input += PLAYER_INPUT_CHANGE_VALUE;
        if(player1Input > 1.0) {
            player1Input = 1.0;
        }
        sound.updatePlayerSound(player1Input);
    } else if(currentPlayer == PLAYER2) {
        player2Input += PLAYER_INPUT_CHANGE_VALUE;
        if(player2Input > 1.0) {
            player2Input = 1.0;
        }
        sound.updatePlayerSound(player2Input);
    }
}

void MainWindow::endPlayerInput() {
    qDebug() << "endPlayerInput";

    if(currentPlayer == PLAYER1 || currentPlayer == PLAYER2) {
        sound.stopPlayerSound();
    }
}

void MainWindow::playGameSound() {
    sound.playGameSound();
}

void MainWindow::quitGame() {
    QApplication::quit();
}

void MainWindow::restartGame() {
    qDebug() << "Restarting game...";
    initGame();
}

