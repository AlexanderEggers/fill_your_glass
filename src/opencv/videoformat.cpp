#include "videoformat.h"
#include <sstream>
VideoFormat::VideoFormat()
    : _frameWidth(0)
    , _frameHeight(0)
    , _framesPerSecond(0)
    , _frameCount(0)
    , _type(0)
{
}


void VideoFormat::setFormat(cv::VideoCapture & videoCapture){
    _frameWidth =  videoCapture.get(CV_CAP_PROP_FRAME_WIDTH);
    _frameHeight = videoCapture.get(CV_CAP_PROP_FRAME_HEIGHT);
    _framesPerSecond = videoCapture.get(CV_CAP_PROP_FPS);
    _frameCount = videoCapture.get(CV_CAP_PROP_FRAME_COUNT);
    if (_framesPerSecond == 0){
        _framesPerSecond = 30;
    }
}
void VideoFormat::setType(int type){
    this->_type = type;
}

int VideoFormat::frameWidth() const {
    return _frameWidth;
}

int VideoFormat::frameHeight() const {
    return _frameHeight;
}

int VideoFormat::framesPerSecond() const {
    return _framesPerSecond;
}

int VideoFormat::frameCount() const {
    return _frameCount;
}

int VideoFormat::type()const{
    return _type;
}
std::string VideoFormat::toString() const{
    std::ostringstream oss;
    oss << "width: " << _frameWidth
        << " height: " << _frameHeight
        << " fps: " << _framesPerSecond
        << " frameCount: " << _frameCount
        << " type: " << _type;
    return oss.str();
}
