#ifndef AUDIOFILE_H
#define AUDIOFILE_H

#include <vector>
#include <QIODevice>
#include <QAudioOutput>
#include "audiofile.h"
#include "audiosource.h"

class AudioDecoder;
class AudioFile : public AudioSource
{
public:
    AudioFile(int bufferSize = 1024);
    ~AudioFile();
    void setFileName(const QString& sourceFileName);
    void setSamplePosition(int samplePosition);
    int  samplePosition() const;
public:
    // implements AudioSource
    virtual const QAudioFormat& format() const;
    virtual qint64 read(float** buffer, qint64 numFrames);
    virtual void start();
    virtual void stop();
private:
    void nextAudioBuffer();
private:
    AudioDecoder* audioDecoder;
    QAudioFormat audioFormat;
    QString sourceFileName;
    int audioBufferPos;
    int numChannels;
    int bufferSize;
    int available;
    std::vector<float> interleavedFloatSamples;
};



#endif // AUDIOFILE_H
