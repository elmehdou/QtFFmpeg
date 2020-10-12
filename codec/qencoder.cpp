#include "qencoder.h"

QEncoder::QEncoder(Sptr<QStream> stream) : QEncoder(stream->getData())
{
}

QEncoder::QEncoder(AVStream *stream) : QCoder()
{
    initializeCoder(stream->codecpar, stream->codecpar->codec_id);
}

QEncoder::QEncoder(AVCodecParameters *parameters, AVCodecID codecID) : QCoder()
{
    initializeCoder(parameters, codecID);
}

QEncoder::QEncoder(AVCodecParameters *parameters, const QString &name) : QCoder()
{
    initializeCoder(parameters, name);
}

AVCodec *QEncoder::findCoder(AVCodecID codecID)
{
    return avcodec_find_encoder(codecID);
}

AVCodec *QEncoder::findCoder(const QString &name)
{
    return avcodec_find_encoder_by_name(name.toStdString().c_str());
}

