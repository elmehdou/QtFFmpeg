#include "qstream.h"

QStream::QStream(AVStream *stream) : QObject()
  , data(stream)
{

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
