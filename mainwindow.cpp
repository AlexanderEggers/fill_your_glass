#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QVBoxLayout"
#include "QHBoxLayout"
#include "QPushButton"
#include "QStackedWidget"
#include "QComboBox"
#include "QDebug"
#include "QLabel"
#include "QTimer"

const int STARTSCREEN = 0, INTRODUCTION_SCREEN = 1, PLAYER1_READY_SCREEN = 2,
PLAYER1_GAME_SCREEN = 3, PLAYER2_READY_SCREEN = 4, PLAYER2_GAME_SCREEN = 5, GAME_DONE_SCREEN = 6;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    stackedWidget(new QStackedWidget),
    source(STARTSCREEN),
    timeLeft(30)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);

    qTimer = new QTimer(this);
    connect(qTimer, SIGNAL(timeout()), this, SLOT(updateGUITime()));

    guiTime1 = new QLabel;
    guiTime1->setAlignment(Qt::AlignRight);

    guiTime2 = new QLabel;
    guiTime2->setAlignment(Qt::AlignRight);

    stackedWidget = new QStackedWidget;
    stackedWidget->addWidget(initStartScreen());
    stackedWidget->addWidget(initIntructionScreen());
    stackedWidget->addWidget(initPlayerReadyScreen(1));
    stackedWidget->addWidget(initGameScreen(1));
    stackedWidget->addWidget(initPlayerReadyScreen(2));
    stackedWidget->addWidget(initGameScreen(2));

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
    connect(button, SIGNAL (released()), this, SLOT (handleButton()));

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
    connect(button, SIGNAL (released()), this, SLOT (handleButton()));

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
    if(player == 1) {
        imageURI = ":/images/player_ready.jpg";
    } else {
        imageURI = ":/images/player_ready.jpg";
    }

    QPixmap image(imageURI);
    image = image.scaled(600,500,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    label->setPixmap(image);

    QPushButton *button = new QPushButton("Ready");
    connect(button, SIGNAL (released()), this, SLOT (handleButton()));

    layout->addWidget(label);
    layout->addWidget(button);

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
    if(player == 1) {
        guiTime1->setText("Remaining time: 30s");
        playername->setText("Player 1");
        imageURI = ":/images/player1_game_screen.jpg";

        headerLayout->addWidget(playername);
        headerLayout->addWidget(guiTime1);
    } else {
        guiTime2->setText("Remaining time: 30s");
        playername->setText("Player 2");
        imageURI = ":/images/player2_game_screen.jpg";

        headerLayout->addWidget(playername);
        headerLayout->addWidget(guiTime2);
    }

    QPixmap image(imageURI);
    image = image.scaled(600,500,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    label->setPixmap(image);

    QPushButton *button = new QPushButton("Confirm");
    connect(button, SIGNAL (released()), this, SLOT (handleButton()));

    QWidget *header = new QWidget;
    header->setLayout(headerLayout);

    layout->addWidget(header);

    layout->addWidget(label);
    layout->addWidget(button);

    widget->setLayout(layout);
    return widget;
}

void MainWindow::handleButton()
{
    qDebug() << "source old: " << source;

    if(qTimer->isActive()) {
        qTimer->stop();
        timeLeft = 30;
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
            source = PLAYER1_GAME_SCREEN;
            stackedWidget->setCurrentWidget(stackedWidget->widget(PLAYER1_GAME_SCREEN));
            qTimer->start(1000);
            break;
        case PLAYER1_GAME_SCREEN:
            source = PLAYER2_READY_SCREEN;
            stackedWidget->setCurrentWidget(stackedWidget->widget(PLAYER2_READY_SCREEN));
            break;
        case PLAYER2_READY_SCREEN:
            source = PLAYER2_GAME_SCREEN;
            stackedWidget->setCurrentWidget(stackedWidget->widget(PLAYER2_GAME_SCREEN));
            qTimer->start(1000);
            break;
        case PLAYER2_GAME_SCREEN:
            source = STARTSCREEN;
            stackedWidget->setCurrentWidget(stackedWidget->widget(STARTSCREEN));
            break;
        default:
            break;
    }

    qDebug() << "source new: " << source;
}

void MainWindow::updateGUITime() {
    timeLeft = timeLeft - 1;

    if(timeLeft == 0) {
        qTimer->stop();
        timeLeft = 30;
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

