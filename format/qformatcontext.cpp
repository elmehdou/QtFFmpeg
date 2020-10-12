#include "qformatcontext.h"

QFormatContext::QFormatContext(const QString &filename): QObject()
  , filename(filename)
  , data(nullptr)
  , streams()
{

}

QFormatContext::~QFormatContext()
{
    clear();
}

void QFormatContext::clear()
{
    if (data) avformat_close_input(&data);

    streams.clear();
}

AVFormatContext *QFormatContext::getData() const
{
    return data;
}

QList<Sptr<QStream>> QFormatContext::getStreams() const
{
    return streams;
}

Sptr<QStream> QFormatContext::getStream(int index) const
{
    for (Sptr<QStream> stream : streams){
        if (stream->getIndex() == index) return stream;
    }

    return nullptr;
}

QString QFormatContext::getFilename() const
{
    return filename;
}
