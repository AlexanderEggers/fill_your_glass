#-------------------------------------------------
#
# Project created by QtCreator 2016-11-28T22:00:26
#
#-------------------------------------------------

QT       += core gui widgets multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fill-your-glass
TEMPLATE = app

INCLUDEPATH += audioengine\
			oscillator\
			main

include(audioengine/audioplayer.pri)
include(oscillator/oscillator.pri)
include(main/main.pri)
include(soundSystem/soundSystem.pri)

DISTFILES +=
