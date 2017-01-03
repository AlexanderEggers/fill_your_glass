#include "facedetection.h"

#include <dlib/opencv.h>
#include <opencv2/highgui/highgui.hpp>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <QDebug>

using namespace std;
using namespace dlib;


FaceDetection::FaceDetection()
{
}


FaceDetection::~FaceDetection()
{
}


int FaceDetection::detectFaces(){

    try
    {
        //download from http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2, extract and copy the path into this string
        string pathToSPDat = "C:/Users/Ninja/Desktop/shape_predictor_68_face_landmarks.dat";
        cv::VideoCapture cap(0);
        if (!cap.isOpened())
        {
            cerr << "Unable to connect to camera" << endl;
            return 1;
        }

        image_window win;

        // Load face detection and pose estimation models.
        frontal_face_detector detector = get_frontal_face_detector();
        shape_predictor predictor;
        deserialize(pathToSPDat) >> predictor;
        // Grab and process frames until the main window is closed by the user.
        while(!win.is_closed())
        {
            // Grab a frame
            cv::Mat temp;
            cap >> temp;
            // Turn OpenCV's Mat into something dlib can deal with.  Note that this just
            // wraps the Mat object, it doesn't copy anything.  So cimg is only valid as
            // long as temp is valid.  Also don't do anything to temp that would cause it
            // to reallocate the memory which stores the image as that will make cimg
            // contain dangling pointers.  This basically means you shouldn't modify temp
            // while using cimg.
            cv_image<bgr_pixel> cimg(temp);

            // Detect faces
            std::vector<rectangle> faces = detector(cimg);
            // Find the pose of each face.
            std::vector<full_object_detection> shapes;
            dlib::point p1;
            for (unsigned long i = 0; i < faces.size(); ++i){
                dlib::full_object_detection shape = predictor(cimg, faces[i]);

                p1 = shape.part(1);
                //qDebug()<<p1.x();

                shapes.push_back(shape);
            }
            // Display it all on the screen
            win.clear_overlay();
            win.set_image(cimg);
            win.add_overlay(render_face_detections(shapes));
            for (dlib::full_object_detection shape: shapes) {
                for(int i=49;i<68;i++) {
                    win.add_overlay(dlib::image_window::overlay_circle(shape.part(i),2, rgb_pixel(255,0,0),std::to_string(i)));
                }
                // landmarks 62 and 66 are the inner lip points that are centered. other pairs are (61,67)->left and (63,65)->right
                int distanceMouth1 = sqrt((shape.part(62).x() - shape.part(66).x())^2 - (shape.part(62).y() - shape.part(66).y())^2);
                if (distanceMouth1 < 10 && distanceMouth1 > 2) {
                    qDebug()<<"Mouth open!";
                } else {
                    qDebug()<<"Mouth closed!";
                }

            }

        }
    }
    catch(serialization_error& e)
    {
        cout << "You need dlib's default face landmarking model file to run this example." << endl;
        cout << "You can get it from the following URL: " << endl;
        cout << "   http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2" << endl;
        cout << endl << e.what() << endl;
    }
    catch(exception& e)
    {
        cout << e.what() << endl;
    }
}
