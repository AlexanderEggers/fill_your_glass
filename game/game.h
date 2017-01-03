#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <QFile>
#include <QAudioOutput>
#include <QWidget>
#include "audioplayer.h"
#include "soundsystem.h"
#include "facedetection.h"

namespace Ui {
class Game;
}

class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = 0);
    ~Game();

private slots:


private:
    void initialize();
    Ui::Game *ui;
    //AudioPlayer audioPlayer;
    //SoundSystem sound;

};

#endif // GAME_H
