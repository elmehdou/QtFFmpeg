#include "qcodeccontext.h"

QCodecContext::QCodecContext(QObject *parent) : QObject(parent)
  , data(nullptr)
{
    allocate();
}

QCodecContext::QCodecContext(AVCodecContext *context): QObject()
  , data(context)
{

}

QCodecContext::QCodecContext(AVCodecParameters *parameters): QObject()
  , data(nullptr)
{
    if (parameters) {
        if (allocate()){
            int ret = copyParameters(parameters);
            if (ret < 0) {
                clear();
            }
        }
    }
}

QCodecContext::~QCodecContext()
{
    clear();
}

void QCodecContext::clear()
{
    if (data) avcodec_free_context(&data);
}

bool QCodecContext::allocate(Sptr<QCodec> codec)
{
    AVCodec *codecData = codec ? codec.data()->getData() : nullptr;
    data = avcodec_alloc_context3(codecData);
    if (!data) return false;

    return true;
}

int QCodecContext::copyParameters(AVStream *stream)
{
    if (stream) return copyParameters(stream->codecpar);

    return -1;
}

int QCodecContext::copyParameters(QStream *stream)
{
    if (stream) return copyParameters(stream->getData());

    return -1;
}

int QCodecContext::copyParameters(AVCodecParameters *parameters)
{
    return avcodec_parameters_from_context(parameters, data);
}


// SETTERS - GETTERS
AVCodecContext *QCodecContext::getData() const
{
    return data;
}

AVCodecID QCodecContext::getID() const
{
    if (!data) return AV_CODEC_ID_NONE;

    return data->codec_id;
}

AVMediaType QCodecContext::getType() const
{
    if (!data) return AVMEDIA_TYPE_UNKNOWN;

    return data->codec_type;
}

AVRational QCodecContext::getTimeBase() const
{
    if (!data) return AVRational{0,0};

    return data->time_base;
}

void QCodecContext::setTimeBase(AVRational value)
{
    if (!data) return;

    data->time_base = value;
}

void QCodecContext::setTimeBase(int numerator, int denominator)
{
    setTimeBase((AVRational){numerator, denominator});
}

uint32_t QCodecContext::getCodecTag() const
{
    if (!data) return 0;

    return data->codec_tag;
}

void QCodecContext::setCodecTag(uint32_t value)
{
    if (!data) return;

    data->codec_tag = value;
}

int QCodecContext::getFlags() const
{
    if (!data) return 0;

    return data->flags;
}

void QCodecContext::setFlags(int value)
{
    if (!data) return;

    data->flags = value;
}
