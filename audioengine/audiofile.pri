# libaudiodecoder
# https://github.com/asantoni/libaudiodecoder
# commented line 19 in audiodecodermediafoundation.h

INCLUDEPATH += audioengine  audioengine/libaudiodecoder/include
HEADERS += audioengine/audiosource.h \
           audioengine/audiofile.h \
           audioengine/libaudiodecoder/include/audiodecoder.h \
           audioengine/libaudiodecoder/include/audiodecoderbase.h \


SOURCES += ../audioengine/audiofile.cpp \

win32{
    DEFINES += _WIN32
    SOURCES += audioengine/libaudiodecoder/src/audiodecoderbase.cpp \
               audioengine/libaudiodecoder/src/audiodecodermediafoundation.cpp
    LIBS    +=  -ldxva2 -lmf -levr -lmfplat -lmfplay -lmfreadwrite -lmfuuid -lole32
}
macx{
    SOURCES += audioengine/libaudiodecoder/src/audiodecoderbase.cpp \
               audioengine/libaudiodecoder/src/audiodecodercoreaudio.cpp
    LIBS += -framework CoreFoundation -framework AudioToolbox
}

