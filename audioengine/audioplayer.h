#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QIODevice>
#include <QAudioFormat>
#include <QAudioOutput>
#include "audiosource.h"
#include "channelbuffer.h"
#include "audioprocessor.h"

class AudioPlayer: public QIODevice
{
    Q_OBJECT
public:
    AudioPlayer(QObject* parent, int bufferSize = 999);
    ~AudioPlayer();
    void start();
    void stop();
    const QAudioFormat& format()const;
    void setAudioSource(AudioSource* audioSource);
    void setAudioProcessor(AudioProcessor* audioProcessor);
public:
    // implement QIODevice
    qint64 readData(char *data, qint64 maxlen);
    qint64 writeData(const char *data, qint64 len);
    qint64 bytesAvailable() const;
private:
    AudioSource* audioSource;
    QAudioOutput* audioOutput;
    QAudioFormat audioFormat;
    int audioBufferPos;
    int numChannels;
    int bufferSize;
    int available;
    ChannelBuffer inputChannelBuffer;
    ChannelBuffer outputChannelBuffer;
    AudioProcessor *audioProcessor;
};

#endif // AUDIOPLAYER_H
