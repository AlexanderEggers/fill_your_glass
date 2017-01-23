#-------------------------------------------------
#
# Project created by QtCreator 2017-01-16T12:55:11
#
#-------------------------------------------------

QT       += core gui widgets multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fill-your-glass
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += "C:\dlib_build\include"

include(src/main/main.pri)
include(src/soundsystem/soundsystem.pri)
include(src/opencv/videoengine.pri)
include(src/facedetection/facedetection.pri)

RESOURCES += \
    $$PWD/res/images.qrc \
    $$PWD/res/sounds.qrc

LIBS += -L"C:\dlib_build\lib" -ldlib
