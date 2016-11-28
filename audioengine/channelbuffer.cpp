#include "channelbuffer.h"

ChannelBuffer::ChannelBuffer()
    : channelBuffer(0)
    , numChannels(0)
    , bufferSize(0)
{

}
ChannelBuffer::~ChannelBuffer(){
    destroy();
}
void ChannelBuffer::resize(int numChannels, int bufferSize){
    destroy();
    this->numChannels = numChannels;
    this->bufferSize = bufferSize;
    channelBuffer = new float*[numChannels];
    for(int c = 0; c < numChannels; c++){
        channelBuffer[c] = new float[bufferSize];
    }
    clear();
}
void ChannelBuffer::destroy(){
    for (int c = 0; c < numChannels; c++){
        delete[] channelBuffer[c];
    }
    delete[] channelBuffer;
    channelBuffer = 0;
    numChannels = 0;
    bufferSize = 0;
}

void ChannelBuffer::clear(){
    for(int c = 0; c < numChannels; c++){
        for(int i = 0; i < bufferSize; i++){
            channelBuffer[c][i] = 0;
        }
    }
}

float** ChannelBuffer::buffer() const{
    return channelBuffer;
}
float* ChannelBuffer::channel(int channelIndex, int offset) const{
    return &channelBuffer[channelIndex][offset];
}
void ChannelBuffer::toShort(short* destination, int destinationOffset, int sourceOffset, int numFrames){
    const int SHORT_MAX_VALUE = 32678;
    const int SHORT_MIN_VALUE = -SHORT_MAX_VALUE;
    for(int c = 0; c < numChannels; c++){
        float* input = &channelBuffer[c][sourceOffset];
        short* output = &destination[destinationOffset*numChannels];
        int outputIndex = c;
        for(int i = 0; i < numFrames; i++){
            float floatValue = input[i] * SHORT_MAX_VALUE;
            if (floatValue >= SHORT_MAX_VALUE){
                floatValue = SHORT_MAX_VALUE -1;
            }
            else if (floatValue < SHORT_MIN_VALUE){
                floatValue = SHORT_MIN_VALUE;
            }
            output[outputIndex] = (short)(floatValue);
            outputIndex += numChannels;
        }
    }

}
void ChannelBuffer::copyTo(ChannelBuffer &other, int numFrames){
    for(int c = 0; c < numChannels; c++){
        for(int i = 0; i < numFrames; i++){
            other.channelBuffer[c][i] = channelBuffer[c][i];
        }
    }
}
