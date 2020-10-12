#include "qvideocodeccontext.h"

QVideoCodecContext::QVideoCodecContext(AVCodecContext *context): QCodecContext(context)
{

}

QVideoCodecContext::QVideoCodecContext(AVCodecParameters *parameters): QCodecContext(parameters)
{

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

    data->height = value;
}
