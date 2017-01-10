#include "game.h"
#include "ui_game.h"
#include <QApplication>
#include <QDebug>
#include <QPixmap>
#include <QIcon>

Game::Game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
    ui->pushButton_2->setVisible(false);
    //int labelWidth = ui->label_startscreen->width();
    //int labelHeight = ui->label_startscreen->height();
    int buttonWidth = ui->pushButton->size().width();
    int buttonHeight = ui->pushButton->size().height();

    QPixmap startscreenPic("D:/fill-your-glass/startscreen.jpg");
    QIcon ButtonIcon(startscreenPic);
    ui->pushButton->setIcon(ButtonIcon);
    ui->pushButton->setIconSize(QSize(buttonWidth,buttonHeight));

   // ui->label_startscreen->setPixmap(startscreenPic.scaled(labelWidth, labelHeight, Qt::KeepAspectRatio));
   // ui->label_startscreen->showFullScreen();
}

Game::~Game()
{
    delete ui;
}


void Game::on_pushButton_clicked()
{
    ui->pushButton->setVisible(false);
    ui->pushButton_2->setVisible(true);
    QPixmap introPic ("D:/fill-your-glass/intro_Pic.jpg");
    ui->pushButton_2->setIcon(introPic);
}
