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
    effect.setSource(QUrl::fromLocalFile(":/test_sound.wav"));
    effect.setLoopCount(QSoundEffect::Infinite);
    effect.setVolume(20);
}

void SoundSystem::handleMouthOpenEvent(){
    qDebug()<<"MouthOpenEvent catched";
    effect.play();
}

void SoundSystem::handleMouthClosedEvent(){
    qDebug()<<"MouthClosedEvent catched";
    effect.stop();
}



/*SoundSystem::SoundSystem(QObject* parent):
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
        QSound::play(":/test_sound.wav");

        //player->play();
        isPlaying = true;
    }

}

void SoundSystem::handleMouthClosedEvent(){
    qDebug()<<"MouthClosedEvent catched";

}*/

