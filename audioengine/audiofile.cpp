#include "AudioFile.h"
#include "audiodecoder.h"
#include <QAudioOutput>
#include <QDebug>
#include <QFile>
// see class Generator in
// http://qt-project.org/doc/qt-4.8/multimedia-audiooutput-audiooutput-cpp.html

AudioFile::AudioFile(int bufferSize)
    : audioDecoder(0)
    , audioBufferPos(0)
    , numChannels(0)
    , bufferSize(bufferSize)
    , available(0)
{
}
AudioFile::~AudioFile(){
    qDebug() << "~AudioFile";
    stop();
}
void AudioFile::stop(){
    delete audioDecoder;
    audioDecoder = 0;
    audioFormat.setSampleType(QAudioFormat::Unknown);
    audioFormat.setChannelCount(0);
    audioFormat.setSampleRate(0);
    audioFormat.setSampleSize(0);
}
void AudioFile::setFileName(const QString &sourceFileName){
    this->sourceFileName = sourceFileName;
}

void AudioFile::start(){
    stop();
    audioDecoder = new AudioDecoder(sourceFileName.toStdString());
    int error = audioDecoder->open();
    if (error == 0){
       audioFormat.setCodec("audio/pcm");
       audioFormat.setByteOrder(QAudioFormat::LittleEndian);
       audioFormat.setChannelCount(audioDecoder->channels());
       audioFormat.setSampleRate(audioDecoder->sampleRate());
       audioFormat.setSampleSize(16);
       audioFormat.setSampleType(QAudioFormat::SignedInt);
       numChannels = audioDecoder->channels();
       interleavedFloatSamples.resize(numChannels*bufferSize);
       available = audioBufferPos = 0;
   }
}

void AudioFile::setSamplePosition(int samplePosition){
    if (audioDecoder){
        audioDecoder->seek(samplePosition);
    }
}

int AudioFile::samplePosition() const{
    if (audioDecoder){
        return audioDecoder->positionInSamples();
    }
    else{
        return 0;
    }
}
const QAudioFormat& AudioFile::format()const{
    return audioFormat;
}


qint64 AudioFile::read(float**buffer, qint64 framesWanted)
{
    qint64 framesCopied = 0;
    while (framesWanted - framesCopied > 0) {
        if (available - audioBufferPos == 0){
            available = audioDecoder->read(bufferSize * numChannels, &interleavedFloatSamples[0]) / numChannels;
            audioBufferPos = 0;
        }

        // convert interleaved to channel buffer
        const qint64 chunk = qMin<int>(available - audioBufferPos, framesWanted - framesCopied);
        for(int c = 0; c < numChannels; c++){
            int srcOffset = audioBufferPos * numChannels + c;
            for(int i = 0; i < chunk; i++){
                buffer[c][i + framesCopied] = interleavedFloatSamples[srcOffset];
                srcOffset += numChannels;
            }
        }

        framesCopied += chunk;
        audioBufferPos += chunk ;
    }
    return framesCopied;

}

