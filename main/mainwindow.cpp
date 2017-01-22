#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QVBoxLayout"
#include "QHBoxLayout"
#include "QPushButton"
#include "QComboBox"
#include "QDebug"
#include <stdlib.h>
#include "QProcess"
#include "facedetection.h"
#include "soundsystem.h"

const int STARTSCREEN = 0, INTRODUCTION_SCREEN = 1, PLAYER1_READY_SCREEN = 2,
PLAYER1_GAME_SCREEN = 3, PLAYER2_READY_SCREEN = 4, PLAYER2_GAME_SCREEN = 5, GAME_RESULT_SCREEN = 6;

const int PLAYER_GAME_TIME = 10;
const int PLAYER1 = 1, PLAYER2 = 2;
const int PLAYER_INPUT_CHANGE_VALUE = 10;

int const MainWindow::EXIT_CODE_REBOOT = -123456789;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    sound(new SoundSystem(parent)),
    faceDetection(new FaceDetection(parent))
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    initGame();
}

void MainWindow::initGame() {
    stackedWidget = new QStackedWidget;
    source = STARTSCREEN;
    timeLeft = PLAYER_GAME_TIME;
    player1Input = 0;
    player2Input = 0;
    currentPlayer = 0;

    qTimer = new QTimer(this);
    connect(qTimer, SIGNAL(timeout()), this, SLOT(updateGUITime()));

    guiTime1 = new QLabel;
    guiTime1->setAlignment(Qt::AlignRight);

    guiTime2 = new QLabel;
    guiTime2->setAlignment(Qt::AlignRight);

    QObject::connect(&faceDetection, SIGNAL(signalMouthOpenEvent(void)),
                            this, SLOT(updatePlayerInput(void)));
    QObject::connect(&faceDetection, SIGNAL(signalMouthClosedEvent(void)),
                            this, SLOT(stopPlayerSound(void)));

    stackedWidget = new QStackedWidget;
    stackedWidget->addWidget(initStartScreen());
    stackedWidget->addWidget(initIntructionScreen());
    stackedWidget->addWidget(initPlayerReadyScreen(PLAYER1));
    stackedWidget->addWidget(initGameScreen(PLAYER1));
    stackedWidget->addWidget(initPlayerReadyScreen(PLAYER2));
    stackedWidget->addWidget(initGameScreen(PLAYER2));

    QVBoxLayout *box = new QVBoxLayout;
    box->addWidget(stackedWidget);

    QWidget *central = centralWidget();
    central->setLayout(box);

    QWidget *startScreen = stackedWidget->widget(STARTSCREEN);
    stackedWidget->setCurrentWidget(startScreen);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QWidget* MainWindow::initStartScreen() {
    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;

    QLabel *label = new QLabel;
    QPixmap image(":/images/intro_Pic.jpg");
    image = image.scaled(600,500,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    label->setPixmap(image);

    QPushButton *button = new QPushButton("Next");
    connect(button, SIGNAL (released()), this, SLOT (showNextWindow()));

    layout->addWidget(label);
    layout->addWidget(button);

    widget->setLayout(layout);
    return widget;
}

QWidget* MainWindow::initIntructionScreen() {
    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;

    QLabel *label = new QLabel;
    QPixmap image(":/images/startscreen.jpg");
    image = image.scaled(600,500,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    label->setPixmap(image);

    QPushButton *button = new QPushButton("Next");
    connect(button, SIGNAL (released()), this, SLOT (showNextWindow()));

    layout->addWidget(label);
    layout->addWidget(button);

    widget->setLayout(layout);
    return widget;
}

QWidget* MainWindow::initPlayerReadyScreen(int player) {
    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;

    QLabel *label = new QLabel;
    QString imageURI = "";
    if(player == PLAYER1) {
        imageURI = ":/images/player_ready.jpg";
    } else {
        imageURI = ":/images/player_ready.jpg";
    }

    QPixmap image(imageURI);
    image = image.scaled(600,500,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    label->setPixmap(image);

    QPushButton *readyButton = new QPushButton("Ready");
    connect(readyButton, SIGNAL (released()), this, SLOT (showNextWindow()));

    QPushButton *gameSoundButton = new QPushButton("Play Game Sound");
    connect(gameSoundButton, SIGNAL (released()), this, SLOT (playGameSound()));

    layout->addWidget(label);
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

    QLabel *label = new QLabel;
    QString imageURI = "";
    if(player == PLAYER1) {
        guiTime1->setText("Remaining time: " + PLAYER_GAME_TIME);
        playername->setText("Player 1");
        imageURI = ":/images/player1_game_screen.jpg";

        headerLayout->addWidget(playername);
        headerLayout->addWidget(guiTime1);
    } else {
        guiTime2->setText("Remaining time: " + PLAYER_GAME_TIME);
        playername->setText("Player 2");
        imageURI = ":/images/player2_game_screen.jpg";

        headerLayout->addWidget(playername);
        headerLayout->addWidget(guiTime2);
    }

    QPixmap image(imageURI);
    image = image.scaled(600,500,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    label->setPixmap(image);

    QPushButton *button = new QPushButton("Confirm");
    connect(button, SIGNAL (released()), this, SLOT (showNextWindow()));

    QWidget *header = new QWidget;
    header->setLayout(headerLayout);

    layout->addWidget(header);

    layout->addWidget(label);
    layout->addWidget(button);

    widget->setLayout(layout);
    return widget;
}

QWidget* MainWindow::initResultScreen() {
    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;

    QLabel *label = new QLabel;
    QString imageURI = "";
    int soundGameValue = sound.getSoundGameValue();
    int player1InputDiff = abs(soundGameValue - player1Input);
    int player2InputDiff = abs(soundGameValue - player2Input);

    if(player1InputDiff < player2InputDiff) {
        imageURI = ":/images/playerOneWins.jpg";
    } else if(player1InputDiff > player2InputDiff) {
        imageURI = ":/images/playerTwoWins.jpg";
    } else {
        imageURI = ":/images/noPlayerWins.jpg";
    }

    QPixmap image(imageURI);
    image = image.scaled(600,500,Qt::IgnoreAspectRatio,Qt::FastTransformation);
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


void MainWindow::showNextWindow()
{
    qDebug() << "source old: " << source;

    if(qTimer->isActive()) {
        qTimer->stop();
        timeLeft = PLAYER_GAME_TIME;
    }

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
            sound.initPlayerSound();
            //faceDetection.startDetectingFaces();
            source = PLAYER1_GAME_SCREEN;
            stackedWidget->setCurrentWidget(stackedWidget->widget(PLAYER1_GAME_SCREEN));
            qTimer->start(1000);
            break;
        case PLAYER1_GAME_SCREEN:
            //faceDetection.stopDetectingFaces();
            source = PLAYER2_READY_SCREEN;
            stackedWidget->setCurrentWidget(stackedWidget->widget(PLAYER2_READY_SCREEN));
            break;
        case PLAYER2_READY_SCREEN:
            sound.initPlayerSound();
            //faceDetection.startDetectingFaces();
            source = PLAYER2_GAME_SCREEN;
            stackedWidget->setCurrentWidget(stackedWidget->widget(PLAYER2_GAME_SCREEN));
            qTimer->start(1000);
            break;
        case PLAYER2_GAME_SCREEN:
            //faceDetection.stopDetectingFaces();
            source = GAME_RESULT_SCREEN;
            stackedWidget->addWidget(initResultScreen());
            stackedWidget->setCurrentWidget(stackedWidget->widget(GAME_RESULT_SCREEN));
            break;
        default:
            break;
    }

    qDebug() << "source new: " << source;
}

void MainWindow::updateGUITime() {
    timeLeft = timeLeft - 1;

    if(timeLeft == 0) {
        showNextWindow();
    }

    QString guiText = "Remaining time: ";
    guiText += QString::number(timeLeft);
    guiText += "s";

    switch (source) {
        case PLAYER1_GAME_SCREEN:
            guiTime1->setText(guiText);
            break;
        case PLAYER2_GAME_SCREEN:
            guiTime2->setText(guiText);
            break;
        default:
            break;
    }
}

void MainWindow::updatePlayerInput() {
    if(currentPlayer == PLAYER1) {
        player1Input += PLAYER_INPUT_CHANGE_VALUE;
        sound.updatePlayerSound(player1Input);
    } else {
        player2Input += PLAYER_INPUT_CHANGE_VALUE;
        sound.updatePlayerSound(player2Input);
    }
}

void MainWindow::stopPlayerSound() {
    sound.stopPlayerSound();
}

void MainWindow::playGameSound() {
    sound.playGameSound();
}

void MainWindow::quitGame() {
    QApplication::quit();
}

void MainWindow::restartGame() {
    qDebug() << "Performing application reboot...";
    qApp->exit( MainWindow::EXIT_CODE_REBOOT );
}

