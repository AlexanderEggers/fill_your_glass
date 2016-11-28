#include <math.h>
#include <stdlib.h>
#include "oscillator.h"

const float pi = 3.1415926f;

Oscillator::Oscillator()
: sampleRate(0), index(0), frequency(0), type(SINE), gain(1)
{}

void Oscillator::initialize(float sampleRate){
    this->sampleRate = sampleRate;
}
void Oscillator::setFrequency(float setFrequency){
    frequency = setFrequency;
}
void Oscillator::setType(Type type){
    this->type = type;
}
void Oscillator::setGain(float gain){
    this->gain = gain;
}

float Oscillator::getValue(){
    switch(type){
    case SINE:
        return sine();
    case SAW:
        return saw();
    case SQUARE:
        return square();
    case TRIANGLE:
        return triangle();
    case NOISE:
        return noise();
    }
}

float Oscillator::sine(){
    float value = sin(2 * pi * index * frequency / sampleRate);
    index++;
    return gain * value;
}
float Oscillator::saw(){
    float period = sampleRate / frequency;
    float modulo = fmod(index, period);
    index++;
    float value = (modulo / period) * 2 - 1;
    return gain * value;
}
float Oscillator::square(){
    float value = sin(2 * pi * index * frequency / sampleRate);
    index++;
    return (value > 0)? gain : -gain;
}
float Oscillator::triangle(){
    float period = sampleRate / frequency;
    float modulo = fmod(index, period);
    index++;

    float value = (modulo / period) * 4;
    if (value < 2){
        return gain * (value - 1);
    }
    else{
        return gain * (1 + 2 - value);
    }
}
float Oscillator::noise()
{
    float random = rand();
    return gain * 2 * random / RAND_MAX - 1;
}


