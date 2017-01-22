#-------------------------------------------------
#
# Project created by QtCreator 2014-07-15T19:38:24
#
#-------------------------------------------------

INCLUDEPATH += src/opencv

SOURCES +=  src/opencv/videoengine.cpp \
            src/opencv/videowidget.cpp \
    src/opencv/videoformat.cpp
HEADERS  += src/opencv/videoengine.h \
            src/opencv/videowidget.h \
            src/opencv/cvmattoqimage.h \
            src/opencv/videoprocessor.h \
    src/opencv/videoformat.h\

include(opencv.pri)
