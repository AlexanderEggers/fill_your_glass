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
    int buttonWidth = ui->pushButton->size().width();
    int buttonHeight = ui->pushButton->size().height();

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
    QPixmap introPic (":/images/intro_Pic.jpg");

}
