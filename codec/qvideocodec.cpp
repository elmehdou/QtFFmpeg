#include "qvideocodec.h"

QVideoCodec::QVideoCodec(AVCodec *codec): QCodec(codec)
{

}

QList<AVPixelFormat> QVideoCodec::getPixelFormats() const
{
    QList<AVPixelFormat> formats;

    if (!data) return formats;
    if (!data->pix_fmts) return formats;

    int i = 0;
    AVPixelFormat format = AV_PIX_FMT_NONE;
    while ((format = data->pix_fmts[i]) != AV_PIX_FMT_NONE){
        formats << format;
        i++;
    }

    return formats;
}
