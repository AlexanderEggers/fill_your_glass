#include "soundsystem.h"
#include "QSound"
#include "QDebug"
#include "QObject"
#include "QWidget"
#include "QMediaPlayer"
#include "QSoundEffect"

SoundSystem::SoundSystem(QObject * parent = 0):
    effect(this),
    soundGameValue(rand() % 90 + 20)
{  
    effect.setSource(QUrl::fromLocalFile(":/sounds/test_sound.wav"));
}

void SoundSystem::playGameSound() {
    effect.setVolume(soundGameValue);
    effect.setLoopCount(1);
    effect.play();
}

void SoundSystem::initPlayerSound() {
    effect.stop();
    effect.setVolume(10);
    effect.setLoopCount(QSoundEffect::Infinite);
}

void SoundSystem::startPlayerSound(){
    effect.stop();
    effect.play();
}

void SoundSystem::updatePlayerSound(int newVolume){
    effect.setVolume(newVolume);
}

void SoundSystem::stopPlayerSound(){
    effect.stop();
}

int SoundSystem::getSoundGameValue() {
    return soundGameValue;
}

