#include "qcodec.h"

QCodec::QCodec(QObject *parent) : QObject(parent)
  , data(nullptr)
{

}

QCodec::QCodec(AVCodec *codec): QObject()
  , data(codec)
{

}

AVCodec *QCodec::getData() const
{
    return data;
}

QString QCodec::getName() const
{
    if (!data) return "";

    return QString::fromUtf8(data->name);
}

AVMediaType QCodec::getType() const
{
    if (!data) return AVMEDIA_TYPE_UNKNOWN;

    return data->type;
}

QList<uint32_t> QCodec::getTags() const
{
    QList<uint32_t> tags {};

    if (!data) return tags;
    if (!data->codec_tags) return tags;

    int i = 0;
    uint32_t tag = data->codec_tags[0];
    while ((tag = data->codec_tags[i]) != 0){
        tags << tag;
        i++;
    }

    return tags;
}
