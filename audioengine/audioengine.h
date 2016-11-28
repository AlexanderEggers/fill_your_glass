#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include "audioplayer.h"
#include "audiofile.h"
#include "channelbuffer.h"

class AudioEngine
{
public:
    AudioEngine(QObject* parent, int bufferSize = 1024);
    void open(const QString& sourceFileName);
    void start();
    void stop();
    void setAudioProcessor(AudioProcessor* audioProcessor);
private:
    int bufferSize;
    ChannelBuffer channelBuffer;
    AudioFile audioFile;
    AudioPlayer audioPlayer;
};

#endif // AUDIOENGINE_H
