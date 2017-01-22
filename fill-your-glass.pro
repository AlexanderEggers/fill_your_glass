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

include(main/main.pri)
include(soundSystem/soundSystem.pri)
include(opencv/videoengine.pri)
include(facedetection/facedetection.pri)

RESOURCES += \
    $$PWD/images.qrc \
    $$PWD/sounds.qrc

LIBS += -L"C:\dlib_build\lib" -ldlib
