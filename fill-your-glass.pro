#-------------------------------------------------
#
# Project created by QtCreator 2016-11-28T22:00:26
#
#-------------------------------------------------

QT       += core gui widgets multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = fill-your-glass
TEMPLATE = app

INCLUDEPATH += audioengine\
                oscillator\
                main\
                "C:\dlib_build\include"

LIBS += -L"C:\dlib_build\lib" -ldlib

QMAKE_CXXFLAGS_RELEASE += /arch:AVX

QMAKE_CXXFLAGS += -DDLIB_JPEG_SUPPORT

include(audioengine/audioplayer.pri)
include(oscillator/oscillator.pri)
include(main/main.pri)
include(soundSystem/soundSystem.pri)
include(../opencv/opencv.pri)
include(../opencv/videoengine.pri)
include(facedetection/facedetection.pri)
include(game/game.pri)

DISTFILES +=
