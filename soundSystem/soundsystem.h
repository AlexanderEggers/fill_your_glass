#include <QMediaPlayer>
#include <QSound>
#include <QSoundEffect>
#include <QObject>
#ifndef SOUNDSYSTEM_H
#define SOUNDSYSTEM_H

class SoundSystem : public QObject {
    Q_OBJECT

public:
    SoundSystem(QObject* parent);
    void play();
    void stop();
    //void init();
    //void stop();
private:
    void load();
    void start();
private:
    QSoundEffect effect;
    //QMediaPlayer* player;
    bool isPlaying;
public slots:
    void handleMouthOpenEvent();
    void handleMouthClosedEvent();
};


#endif // SOUNDSYSTEM_H
