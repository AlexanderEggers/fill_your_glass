#include "audioengine.h"

AudioEngine::AudioEngine(QObject* parent, int bufferSize)
    : bufferSize(bufferSize)
    , audioPlayer(parent)
{
    audioPlayer.setAudioSource(&audioFile);
}

void AudioEngine::open(const QString& sourceFileName){
    audioFile.setFileName(sourceFileName);
}

void AudioEngine::start(){
    audioPlayer.start();
}

void AudioEngine::stop(){
    audioPlayer.stop();
}
void AudioEngine::setAudioProcessor(AudioProcessor *audioProcessor){
    audioPlayer.setAudioProcessor(audioProcessor);
}
