#ifndef CHANNELBUFFER_H
#define CHANNELBUFFER_H

class ChannelBuffer
{
public:
    ChannelBuffer();
    ~ChannelBuffer();
    void resize(int numChannels, int bufferSize);
    void clear();
    float** buffer() const;
    float* channel(int channelIndex, int offset = 0)const;
    void toShort(short* destination, int destinationOffset, int sourceOffset, int numFrames);
    void copyTo(ChannelBuffer& other, int numFrames);
private:
    void destroy();
    float** channelBuffer;
    int numChannels;
    int bufferSize;
};

#endif // CHANNELBUFFER_H
