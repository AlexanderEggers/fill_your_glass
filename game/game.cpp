#include "game.h"
#include "ui_game.h"
#include <QApplication>
#include <QDebug>

Game::Game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
}

Game::~Game()
{
    delete ui;
}



//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    Game w;
//    w.show();

//    return a.exec();
//}
