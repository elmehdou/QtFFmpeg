#include "qstream.h"

QStream::QStream(AVStream *stream) : QObject()
  , data(stream)
{

}

int QStream::copyParameters(AVStream *stream)
{
    if (!stream) return -1;

    return avcodec_parameters_copy(data->codecpar, stream->codecpar);
}

int QStream::copyParameters(Sptr<QStream> stream)
{
    if (!stream) return -1;

    return copyParameters(stream->getData());
}

int QStream::copyParameters(AVCodecContext *context)
{
    if (!context) return -1;

    return avcodec_parameters_from_context(data->codecpar, context);
}

int QStream::copyParameters(Sptr<QCodecContext> context)
{
    if (!context) return -1;

    return copyParameters(context->getData());
}

AVStream *QStream::getData() const
{
    return data;
}

AVCodecParameters *QStream::getCodecParameters() const
{
    if (!data) return nullptr;

    return data->codecpar;
}

int QStream::getIndex()
{
    if (!data) return -1;

    return data->index;
}

AVRational QStream::getTimeBase() const
{
    if (!data) return AVRational{0,0};

    return data->time_base;
}
