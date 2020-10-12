#include "qiformatcontext.h"

QIFormatContext::QIFormatContext(const QString filename) : QFormatContext(filename)
{
    if (!filename.length()) return;

    if (openInput() < 0) return;

    if (findStreamInfo() < 0)
        clear();
}

bool QIFormatContext::allocate()
{
    clear();

    data = avformat_alloc_context();
    if (!data) {
        return false;
    }
    return true;
}

int QIFormatContext::openInput(AVInputFormat *inputFormat, AVDictionary **options)
{
    clear();

    return avformat_open_input(&data, filename.toStdString().c_str(), inputFormat, options);
}

int QIFormatContext::findStreamInfo(AVDictionary **options)
{
    int ret = avformat_find_stream_info(data, options);
    if (ret >= 0) {
        for (unsigned int i = 0; i < data->nb_streams; i++){
            streams << Sptr<QStream>::create(data->streams[i]);
        }
    }

    return ret;
}

void QIFormatContext::dump()
{
    av_dump_format(data, 0, nullptr, 0);
}
