#include "soundsystem.h"
#include "QSound"
#include "QDebug"
#include "QObject"
#include "QWidget"
#include "QMediaPlayer"
#include "QSoundEffect"
#include <ctime>

SoundSystem::SoundSystem(QObject * parent = 0):
    effect(this)
{  
    effect.setSource(QUrl::fromLocalFile(":/sounds/game_sound.wav"));
}

void SoundSystem::initGameSound() {
    soundGameValue = getTrueRandom();
}

void SoundSystem::playGameSound() {
    qDebug() << soundGameValue;

    effect.stop();
    effect.setVolume(soundGameValue);
    effect.setLoopCount(1);
    effect.play();
}

void SoundSystem::stopGameSound() {
    effect.stop();
}

void SoundSystem::initPlayerSound() {
    effect.stop();
    effect.setVolume(0.02);
    effect.setLoopCount(QSoundEffect::Infinite);
}

void SoundSystem::startPlayerSound(){
    effect.stop();
    effect.play();
}

void SoundSystem::updatePlayerSound(double newVolume){
    effect.setVolume(newVolume);
}

void SoundSystem::stopPlayerSound(){
    effect.stop();
}

double SoundSystem::getSoundGameValue() {
    return soundGameValue;
}

double SoundSystem::getTrueRandom() {
    srand(time(NULL));
    return ((float)(rand() % 100 + 5)) / (float)100;
}

