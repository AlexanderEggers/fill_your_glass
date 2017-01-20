#include "soundsystem.h"
#include "QSound"
#include "QDebug"
#include "QObject"
#include "QWidget"
#include "QMediaPlayer"
#include "QSoundEffect"

SoundSystem::SoundSystem(QObject * parent = 0):
    effect(this)
{  
}

void SoundSystem::initSound() {
    soundGameValue = rand() % 90 + 20;
    effect.setSource(QUrl::fromLocalFile(":/test_sound.wav"));
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

void SoundSystem::updatePlayerSound(int newVolume){
    effect.stop();
    effect.setVolume(newVolume);
    effect.play();
}

void SoundSystem::stopPlayerSound(){
    effect.stop();
}

int SoundSystem::getSoundGameValue() {
    return soundGameValue;
}

