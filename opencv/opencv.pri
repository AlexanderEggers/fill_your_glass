INCLUDEPATH += opencv
HEADERS += opencv/cvmattoqimage.h

win32 {
    INCLUDEPATH += $$(OPENCV_DIR)\..\..\include
    LIBS += -L$$(OPENCV_DIR)\lib
    Release:LIBS +=  -lopencv_world310
    Debug:LIBS +=  -lopencv_world310d
}
macx {
        QT_CONFIG -= no-pkg-config
        CONFIG  += link_pkgconfig
    PKGCONFIG += opencv
}
linux {
    INCLUDEPATH += /usr/local/include
    LIBS += -L/usr/local/lib
    LIBS +=  -lopencv_core -lopencv_highgui -lopencv_imgproc
}
