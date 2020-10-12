QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        codec/qaudiocodec.cpp \
        codec/qcodec.cpp \
        codec/qcoder.cpp \
        codec/qdecoder.cpp \
        codec/qencoder.cpp \
        codec/qvideocodec.cpp \
        codec/context/qaudiocodeccontext.cpp \
        codec/context/qcodeccontext.cpp \
        codec/context/qvideocodeccontext.cpp \
        format/qformatcontext.cpp \
        format/qiformatcontext.cpp \
        format/qoformatcontext.cpp \
        format/qstream.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    codec/qaudiocodec.h \
    codec/qcodec.h \
    codec/qcoder.h \
    codec/qdecoder.h \
    codec/qencoder.h \
    codec/qvideocodec.h \
    codec/context/qaudiocodeccontext.h \
    codec/context/qcodeccontext.h \
    codec/context/qvideocodeccontext.h \
    ffmpeg.h \
    format/qformatcontext.h \
    format/qiformatcontext.h \
    format/qoformatcontext.h \
    format/qstream.h

INCLUDEPATH += $$PWD/ffmpeg/include

LIBS += -L$$PWD/ffmpeg/lib

LIBS += -lavformat   \
        -lavcodec    \
        -lavutil     \
        -lpostproc   \
        -lavfilter   \
        -lavdevice   \
        -lswresample \
        -lswscale    \
