#include "QMediaPlayer"
#include "QObject"
#ifndef SOUNDOBJECT_H
#define SOUNDOBJECT_H

class SoundSystem {
public:
    SoundSystem(QObject* parent);
    void init();
    void stop();
private:
    void load();
    void start();
private:
    QMediaPlayer* player;
};


#endif // SOUNDOBJECT_H
