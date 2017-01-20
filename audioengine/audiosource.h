#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H

#include <QAudioFormat>

class AudioSource{
public:
    virtual ~AudioSource(){}
    virtual const QAudioFormat& format() const = 0;
    virtual qint64 read(float** buffer, qint64 numFrames) = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
};

#endif // AUDIOSOURCE_H
