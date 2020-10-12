#include "qaudiocodec.h"

QAudioCodec::QAudioCodec(AVCodec *codec): QCodec(codec)
{

}

QList<AVSampleFormat> QAudioCodec::getSampleFormats() const
{
    QList<AVSampleFormat> formats;

    if (!data) return formats;
    if (!data->sample_fmts) return formats;

    int i = 0;
    AVSampleFormat format = AV_SAMPLE_FMT_NONE;
    while ((format = data->sample_fmts[i]) != AV_SAMPLE_FMT_NONE){
        formats << format;
        i++;
    }

    return formats;
}
