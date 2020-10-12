#ifndef QVIDEOCODECCONTEXT_H
#define QVIDEOCODECCONTEXT_H

#include "qcodeccontext.h"

#include <format/qiformatcontext.h>



class QVideoCodecContext : public QCodecContext
{
    Q_OBJECT
public:
    QVideoCodecContext(AVCodecContext *context);
    QVideoCodecContext(AVCodecParameters *parameters);

    int copyParameters(Sptr<QVideoCodecContext> context);

    void guessFramerate(AVFormatContext *formatContext, AVStream *stream);
    void guessFramerate(Sptr<QIFormatContext> formatContext, Sptr<QStream> stream);

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
