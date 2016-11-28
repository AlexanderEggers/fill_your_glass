#ifndef OSCILLATORSOURCE_H
#define OSCILLATORSOURCE_H

#include <vector>

#include "audiosource.h"
#include "oscillator.h"

class OscillatorSource: public AudioSource
{
public:
    OscillatorSource();
    virtual const QAudioFormat& format() const;
    virtual qint64 read(float** buffer, qint64 numFrames);
    virtual void start();
    virtual void stop();
    void setSelectedOscillator(int index);
    void setFrequency(float frequency);
    void setNote(int noteNumber);
    void setGain(float decibel);
private:
    float createSample();
private:
    QAudioFormat audioFormat;
    Oscillator oscillator;
};

#endif // OSCILLATORSOURCE_H
