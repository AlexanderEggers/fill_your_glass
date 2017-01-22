#ifndef VIDEOFORMAT_H
#define VIDEOFORMAT_H
#include <opencv2/opencv.hpp>

class VideoFormat
{
public:
    VideoFormat();
    void setFormat(cv::VideoCapture & videoCapture);
    void setType(int type);
    int frameWidth()const ;
    int frameHeight() const;
    int framesPerSecond()const;
    int frameCount()const;
    int type()const;
    std::string toString() const;
private:
    int _frameWidth;
    int _frameHeight;
    int _framesPerSecond;
    int _frameCount;
    int _framePosition;
    int _type;
 };

#endif // VIDEOFORMAT_H
