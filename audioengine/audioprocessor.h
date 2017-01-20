#ifndef AUDIOPROCESSOR_H
#define AUDIOPROCESSOR_H

#include <QAudioFormat>

class AudioProcessor
{
public:
    virtual ~AudioProcessor(){}
    virtual void startProcessing(const QAudioFormat& format) = 0;
    virtual void process(float**input, float** output, int numFrames) = 0;
    virtual void stopProcessing() = 0;
};

#endif // AUDIOPROCESSOR_H
