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

int QCoder::open(AVDictionary **options)
{
    return avcodec_open2(context->getData(), codec->getData(), options);
}
