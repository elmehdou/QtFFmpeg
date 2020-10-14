#include "qvideocodeccontext.h"

#include <QDebug>

#include <codec/qvideocodec.h>

QVideoCodecContext::QVideoCodecContext(AVCodec *codec): QCodecContext(codec)
{

}

QVideoCodecContext::QVideoCodecContext(Sptr<QCodec> codec): QCodecContext(codec)
{

}

QVideoCodecContext::QVideoCodecContext(AVCodecContext *context): QCodecContext(context)
{

}

QVideoCodecContext::QVideoCodecContext(AVCodecParameters *parameters): QCodecContext(parameters)
{

}

int QVideoCodecContext::copyContext(Sptr<QVideoCodecContext> context)
{
    return copyContext(context.dynamicCast<QCodecContext>());
}

int QVideoCodecContext::copyContext(Sptr<QCodecContext> context)
{
    if (!context) return -1;

    Sptr<QVideoCodecContext> videoContext = context.dynamicCast<QVideoCodecContext>();
    if (videoContext) {
        setWidth(videoContext->getWidth());
        setHeight(videoContext->getHeight());
        setSampleAspectRation(videoContext->getSampleAspectRatio());
        setTimeBase(av_inv_q(videoContext->getFramerate()));
    }

    return 0;
}

void QVideoCodecContext::guessFramerate(AVFormatContext *formatContext, AVStream *stream)
{
    if (!formatContext || !stream) return;

    setFramerate(av_guess_frame_rate(formatContext, stream, nullptr));
}

void QVideoCodecContext::guessFramerate(Sptr<QIFormatContext> formatContext, Sptr<QStream> stream)
{
    if (!formatContext || !stream) return;

    setFramerate(av_guess_frame_rate(formatContext->getData(), stream->getData(), nullptr));
}

AVRational QVideoCodecContext::getFramerate() const
{
    if (!data) return AVRational{0,0};

    return data->framerate;
}

void QVideoCodecContext::setFramerate(AVRational value)
{
    if (!data) return;

    data->framerate = value;
}

int QVideoCodecContext::getWidth() const
{
    if (!data) return 0;

    return data->width;
}

void QVideoCodecContext::setWidth(int value)
{
    if (!data) return;

    data->width = value;
}

int QVideoCodecContext::getHeight() const
{
    if (!data) return 0;

    return data->height;
}

void QVideoCodecContext::setHeight(int value) const
{
    if (!data) return;

    data->height = value;
}

AVRational QVideoCodecContext::getSampleAspectRatio() const
{
    if (!data) return AVRational{0,0};

    return data->sample_aspect_ratio;
}

void QVideoCodecContext::setSampleAspectRation(AVRational value)
{
    if (!data) return;

    data->sample_aspect_ratio = value;
}

AVPixelFormat QVideoCodecContext::getPixelFormat() const
{
    if (!data) return AV_PIX_FMT_NONE;

    return data->pix_fmt;
}

void QVideoCodecContext::setPixelFormat(AVPixelFormat value)
{
    if (!data) return;

    data->pix_fmt = value;
}
