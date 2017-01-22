#include "soundsystem.h"
#include "QSound"
#include "QDebug"
#include "QObject"
#include "QWidget"
#include "QMediaPlayer"
#include "QSoundEffect"

SoundSystem::SoundSystem(QObject * parent = 0):
    effect(this),
    soundGameValue(((float)(rand() % 100 + 1)) / 100)
{  
    effect.setSource(QUrl::fromLocalFile(":/sounds/test_sound.wav"));
}

void SoundSystem::playGameSound() {
    qDebug() << soundGameValue;

    effect.setVolume(soundGameValue);
    effect.setLoopCount(1);
    effect.play();
}

void SoundSystem::initPlayerSound() {
    effect.stop();
    effect.setVolume(0.10);
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

int SoundSystem::getSoundGameValue() {
    return soundGameValue;
}

