#ifndef QVIDEOCODECCONTEXT_H
#define QVIDEOCODECCONTEXT_H

#include "qcodeccontext.h"



class QVideoCodecContext : public QCodecContext
{
    Q_OBJECT
public:
    QVideoCodecContext(AVCodecContext *context);
    QVideoCodecContext(AVCodecParameters *parameters);

    // SETTERS - GETTERS
    int getWidth() const;
    void setWidth(int value);

    int getHeight() const;
    void setHeight(int value) const;

    AVRational getFramerate() const;
    void setFramerate(AVRational value);

    AVRational getSampleAspectRatio() const;
    void setSampleAspectRation(AVRational value);

    AVPixelFormat getPixelFormat() const;
    void setPixelFormat(AVPixelFormat value);

};

#endif // QVIDEOCODECCONTEXT_H
