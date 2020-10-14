#ifndef QVIDEOCODECCONTEXT_H
#define QVIDEOCODECCONTEXT_H

#include "qcodeccontext.h"

#include <format/qiformatcontext.h>



class QVideoCodecContext : public QCodecContext
{
    Q_OBJECT
public:
    QVideoCodecContext(AVCodec *codec);
    QVideoCodecContext(Sptr<QCodec> codec);

    QVideoCodecContext(AVCodecContext *context);

    QVideoCodecContext(AVCodecParameters *parameters);

    int copyContext(Sptr<QVideoCodecContext> context);
    int copyContext(Sptr<QCodecContext> context) override;

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
