#ifndef OSCILLATOR
#define OSCILLATOR


class Oscillator{
public:
    Oscillator();
    enum Type {SINE, TRIANGLE, SQUARE, SAW, NOISE};
    void initialize(float sampleRate);
    void setFrequency(float frequency);
    void setType(Type type);
    void setGain(float gain);
    float getValue();
private:
    float sine();
    float saw();
    float triangle();
    float square();
    float noise();
private:
    int index;
    float sampleRate;
    float frequency;
    float gain;
    Type type;
};

#endif // OSCILLATOR

