#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <QFile>
#include <QAudioOutput>
#include <QWidget>
#include <QEvent>
#include <QStackedWidget>

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
   // void on_pushButton_clicked();
    void handleButton();

private:
    int source;
    void initialize();
    QStackedWidget *stackedWidget;
    Ui::Game *ui;
    QWidget *initStartScreen();
    QWidget *initInstructionScreen();
    QWidget *initPlayerReadyScreen(int player);
    QWidget *initGameScreen(int player);

    //AudioPlayer audioPlayer;
    //SoundSystem sound;

};

#endif // GAME_H
