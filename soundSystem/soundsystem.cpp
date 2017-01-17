#include "soundsystem.h"
#include "QSound"
#include "QDebug"
#include "QObject"
#include "QWidget"
#include "QMediaPlayer"

SoundSystem::SoundSystem(QObject* parent):
    isPlaying(false)
{
    player = new QMediaPlayer(parent);
    player->setVolume(20);
}

void SoundSystem::init(){
    load();
    start();
}

void SoundSystem::load(){
    player->setMedia(QUrl("qrc:/test.mp3"));
}

void SoundSystem::start(){
    player->play();
}

void SoundSystem::stop(){
    player->stop();
}


void SoundSystem::handleMouthOpenEvent(){
    qDebug()<<"MouthOpenEvent catched";
    if (!isPlaying) {
        qDebug()<<"playing sound";
        // angeblich funktiniert QSound auch asynchron, deswegen hab ich es damit versucht. Wird aber trotzdem
        // erst nach schließen des facetracking fensters gestartet
        //QSound::play(":/test_sound.wav");

        player->play();
        isPlaying = true;
    }

}

void SoundSystem::handleMouthClosedEvent(){
    qDebug()<<"MouthClosedEvent catched";

}

