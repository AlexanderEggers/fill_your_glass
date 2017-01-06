#include "soundsystem.h"
#include "QSound"
#include "QDebug"
#include "QObject"
#include "QWidget"
#include "QMediaPlayer"

SoundSystem::SoundSystem(QObject* parent)
{
    player = new QMediaPlayer(parent);
    player->setVolume(20);
}

void SoundSystem::init(){
    load();
    start();
}

void SoundSystem::load(){
    player->setMedia(QUrl("qrc:/test_sound.wav"));
}

void SoundSystem::start(){
    player->play();
}

void SoundSystem::stop(){
    player->stop();
}
