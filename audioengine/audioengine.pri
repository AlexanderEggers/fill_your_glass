# libaudiodecoder
# https://github.com/asantoni/libaudiodecoder
# commented line 19 in audiodecodermediafoundation.h

INCLUDEPATH += audioengine  audioengine/libaudiodecoder/include
HEADERS += audioengine/audioengine.h \
           audioengine/audioprocessor.h \
           audioengine/audiosource.h \
           audioengine/audiofile.h \
           audioengine/audioplayer.h \
           audioengine/libaudiodecoder/include/audiodecoder.h \
           audioengine/libaudiodecoder/include/audiodecoderbase.h \
           audioengine/channelbuffer.h


SOURCES +=  audioengine/audiofile.cpp \
            audioengine/audioplayer.cpp \
            audioengine/audioengine.cpp \
            audioengine/channelbuffer.cpp


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

