#include "qdecoder.h"

QDecoder::QDecoder(Sptr<QStream> stream) : QDecoder(stream->getData())
{
}

QDecoder::QDecoder(AVStream *stream) : QCoder()
{
    initializeCoder(stream->codecpar, stream->codecpar->codec_id);
}

QDecoder::QDecoder(AVCodecParameters *parameters, AVCodecID codecID) : QCoder()
{
    initializeCoder(parameters, codecID);
}

QDecoder::QDecoder(AVCodecParameters *parameters, const QString &name) : QCoder()
{
    initializeCoder(parameters, name);
}

AVCodec *QDecoder::findCoder(AVCodecID codecID)
{
    return avcodec_find_decoder(codecID);
}

AVCodec *QDecoder::findCoder(const QString &name)
{
    return avcodec_find_decoder_by_name(name.toStdString().c_str());
}
