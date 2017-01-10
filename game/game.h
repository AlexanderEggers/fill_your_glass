#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <QFile>
#include <QAudioOutput>
#include <QWidget>
#include <QEvent>

namespace Ui {
class Game;
}

class Game : public QWidget
{

public:
    explicit Game(QWidget *parent = 0);
    ~Game();

private slots:
    void on_pushButton_clicked();

private:
    void initialize();
    Ui::Game *ui;
    //AudioPlayer audioPlayer;
    //SoundSystem sound;

};

#endif // GAME_H
