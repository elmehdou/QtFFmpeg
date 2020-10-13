#include "qencoder.h"

QEncoder::QEncoder(AVStream *stream, AVCodecID codecID) : QCoder()
{
    initializeCoder(stream->codecpar, codecID);
}

QEncoder::QEncoder(AVStream *stream, const QString &codecName) : QCoder()
{
    initializeCoder(stream->codecpar, codecName);
}

QEncoder::QEncoder(Sptr<QStream> stream, AVCodecID codecID) : QEncoder(stream->getData(), codecID)
{

}

QEncoder::QEncoder(Sptr<QStream> stream, const QString &codecName) : QEncoder(stream->getData(), codecName)
{

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

