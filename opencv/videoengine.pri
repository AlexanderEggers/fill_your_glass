#-------------------------------------------------
#
# Project created by QtCreator 2014-07-15T19:38:24
#
#-------------------------------------------------

INCLUDEPATH += opencv

SOURCES +=  opencv/videoengine.cpp \
            opencv/videowidget.cpp \
    opencv/videoformat.cpp
HEADERS  += opencv/videoengine.h \
            opencv/videowidget.h \
            opencv/cvmattoqimage.h \
            opencv/videoprocessor.h \
    opencv/videoformat.h\

include(opencv.pri)
