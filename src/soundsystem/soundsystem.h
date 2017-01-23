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
    void initGameSound();
    double getSoundGameValue();
    void playGameSound();
    void stopGameSound();
    void initPlayerSound();
    void startPlayerSound();
    void updatePlayerSound(double newVolume);
    void stopPlayerSound();
private:
    QSoundEffect effect;
    double soundGameValue;
    double getTrueRandom();
};


#endif // SOUNDSYSTEM_H
