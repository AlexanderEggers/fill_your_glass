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
    int getSoundGameValue();
    void playGameSound();
    void initPlayerSound();
    void startPlayerSound();
    void updatePlayerSound(double newVolume);
    void stopPlayerSound();
private:
    QSoundEffect effect;
    const double soundGameValue;
private:
    double fRand(double fMin, double fMax);
};


#endif // SOUNDSYSTEM_H
