#include "qaudiocodec.h"
#include "qcoder.h"
#include "qvideocodec.h"

#include <QDebug>

#include <codec/context/qaudiocodeccontext.h>
#include <codec/context/qvideocodeccontext.h>

QCoder::QCoder() : QObject()
  , codec(nullptr)
  , context(nullptr)
{

}

Sptr<QCodec> QCoder::getCodec() const
{
    return codec;
}

Sptr<QCodecContext> QCoder::getContext() const
{
    return context;
}

void QCoder::initializeCoder(AVCodecParameters *parameters, AVCodecID codecID)
{
    if (!parameters) return;

    if (codecID == AV_CODEC_ID_NONE) codecID = parameters->codec_id;

    switch (parameters->codec_type) {
    case AVMEDIA_TYPE_VIDEO:
        codec = Sptr<QVideoCodec>::create(findCoder(codecID));
        context = Sptr<QVideoCodecContext>::create(parameters);
        return;
    case AVMEDIA_TYPE_AUDIO:
        codec = Sptr<QAudioCodec>::create(findCoder(codecID));
        context = Sptr<QAudioCodecContext>::create(parameters);
        return;
    default:
        codec = Sptr<QCodec>::create(findCoder(codecID));
        context = Sptr<QCodecContext>::create(parameters);
    }
}

void QCoder::initializeCoder(AVCodecParameters *parameters, const QString &name)
{
    if (!parameters) return;

    if (name.isEmpty()) return initializeCoder(parameters, parameters->codec_id);

    switch (parameters->codec_type) {
    case AVMEDIA_TYPE_VIDEO:
        codec = Sptr<QVideoCodec>::create(findCoder(name));
        context = Sptr<QVideoCodecContext>::create(parameters);
        return;
    case AVMEDIA_TYPE_AUDIO:
        codec = Sptr<QAudioCodec>::create(findCoder(name)); return;
        context = Sptr<QAudioCodecContext>::create(parameters);
        return;
    default:
        codec = Sptr<QCodec>::create(findCoder(name)); return;
        context = Sptr<QCodecContext>::create(parameters);
    }
}

int QCoder::open(AVDictionary **options)
{
    return avcodec_open2(context->getData(), codec->getData(), options);
}
