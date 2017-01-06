#ifndef FACEDETECTION_H
#define FACEDETECTION_H

#include <dlib/opencv.h>
#include <opencv2/highgui/highgui.hpp>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <QObject>

using namespace std;
using namespace dlib;

class FaceDetection : public QObject
{
    Q_OBJECT

public:
    FaceDetection();
    ~FaceDetection();
    int detectFaces();
private:
    bool isMouthOpen;
    int mouthOpenCounter;
    int const mouthOpenCounterThreshold;
signals:
    void signalMouthOpenEvent();
};

#endif // FACEDETECTION_H
