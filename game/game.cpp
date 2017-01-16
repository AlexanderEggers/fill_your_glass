#include "game.h"
#include "ui_game.h"
#include <QApplication>
#include <QPixmap>
#include <QIcon>
#include <QStackedWidget>
#include "QVBoxLayout"
#include "QHBoxLayout"
#include "QPushButton"
#include "QComboBox"
#include "QDebug"
#include "QLabel"
#include <QWidget>

Game::Game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game),
    stackedWidget(new QStackedWidget),
    source(0)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    Game::setWindowTitle("Fill Your Glass");

    stackedWidget = new QStackedWidget;
    stackedWidget->addWidget(initStartScreen());
    stackedWidget->addWidget(initInstructionScreen());
    stackedWidget->addWidget(initPlayerReadyScreen(1));
    stackedWidget->addWidget(initGameScreen(1));
    stackedWidget->addWidget(initPlayerReadyScreen(2));
    stackedWidget->addWidget(initGameScreen(2));

    QVBoxLayout *box = new QVBoxLayout;
    box->addWidget(stackedWidget);

    QWidget *central = ui->widget;
    central->setLayout(box);

    QWidget *bla = stackedWidget->widget(0);
    stackedWidget->setCurrentWidget(bla);

}

Game::~Game()
{
    delete ui;
}

QWidget* Game::initStartScreen() {
    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;

    QLabel *label = new QLabel;
    QPixmap image(":/images/intro_Pic.jpg");
    image = image.scaled(400,300,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    label->setPixmap(image);

    QPushButton *button = new QPushButton("Next");
    connect(button, SIGNAL (released()), this, SLOT (handleButton()));

    layout->addWidget(label);
    layout->addWidget(button);

    widget->setLayout(layout);
    return widget;
}
QWidget* Game::initInstructionScreen() {
    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;

    QLabel *label = new QLabel;
    QPixmap image(":/images/startscreen.jpg");
    image = image.scaled(400,300,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    label->setPixmap(image);

    QPushButton *button = new QPushButton("Next");
    connect(button, SIGNAL (released()), this, SLOT (handleButton()));

    layout->addWidget(label);
    layout->addWidget(button);

    widget->setLayout(layout);
    return widget;
}

QWidget* Game::initPlayerReadyScreen(int player) {
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
    image = image.scaled(400,300,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    label->setPixmap(image);

    QPushButton *button = new QPushButton("Ready");
    connect(button, SIGNAL (released()), this, SLOT (handleButton()));

    layout->addWidget(label);
    layout->addWidget(button);

    widget->setLayout(layout);
    return widget;
}

QWidget* Game::initGameScreen(int player) {
    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;

    QLabel *label = new QLabel;

    QString imageURI = "";
    if(player == 1) {
        imageURI = ":/images/player1_game_screen.jpg";
    } else {
        imageURI = ":/images/player2_game_screen.jpg";
    }

    QPixmap image(imageURI);
    image = image.scaled(400,300,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    label->setPixmap(image);

    QPushButton *button = new QPushButton("Confirm");
    connect(button, SIGNAL (released()), this, SLOT (handleButton()));

    layout->addWidget(label);
    layout->addWidget(button);

    widget->setLayout(layout);
    return widget;
}

void Game::handleButton()
{
    qDebug() << "source old" << source;

    switch (source) {
    case 0:
        source = 1;
        qDebug() << "source" << source;
        stackedWidget->setCurrentWidget(stackedWidget->widget(1));
        break;
    case 1:
        source = 2;
        qDebug() << "source" << source;
        stackedWidget->setCurrentWidget(stackedWidget->widget(2));
        break;
    case 2:
        source = 3;
        qDebug() << "source" << source;
        stackedWidget->setCurrentWidget(stackedWidget->widget(3));
        break;
    case 3:
        source = 4;
        qDebug() << "source" << source;
        stackedWidget->setCurrentWidget(stackedWidget->widget(4));
        break;
    case 4:
        source = 5;
        qDebug() << "source" << source;
        stackedWidget->setCurrentWidget(stackedWidget->widget(5));
        break;
    case 5:
        source = 0;
        qDebug() << "source" << source;
        stackedWidget->setCurrentWidget(stackedWidget->widget(0));
        break;
    default:
        break;
    }
}


