INCLUDEPATH += ../opencv
HEADERS += ../opencv/cvmattoqimage.h

win32 {
#  für Windows muss die Umgebungsvariable OPENCV_DIR gesetzt sein 
#  auf den Pfad der OpenCV-Installation
#  Beispiel: C:\opencv\opencv-3.1.0\opencv\build\x64\vc14

    INCLUDEPATH += $$(OPENCV_DIR)\..\..\include
    LIBS += -L$$(OPENCV_DIR)\lib
    Release:LIBS +=  -lopencv_world310
    Debug:LIBS +=  -lopencv_world310d
}
macx {
# https://www.learnopencv.com/configuring-qt-for-opencv-on-osx/
# (WS1617 von Hennes Römmer getestet, Danke!)
	QT_CONFIG -= no-pkg-config
	CONFIG  += link_pkgconfig
    PKGCONFIG += opencv
}
linux {
# im WS1617 nicht getestet
    INCLUDEPATH += /usr/local/include
    LIBS += -L/usr/local/lib
    LIBS +=  -lopencv_core -lopencv_highgui -lopencv_imgproc
}
