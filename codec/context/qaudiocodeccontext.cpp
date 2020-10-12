#include "qaudiocodeccontext.h"

QAudioCodecContext::QAudioCodecContext(AVCodecContext *context): QCodecContext(context)
{

}

QAudioCodecContext::QAudioCodecContext(AVCodecParameters *parameters): QCodecContext(parameters)
{

}

int QAudioCodecContext::getSampleRate() const
{
    if (!data) return 0;

    return data->sample_rate;
}

void QAudioCodecContext::setSampleRate(int value)
{
    if (!data) return;

    data->sample_rate = value;
}

uint64_t QAudioCodecContext::getChannelLayout() const
{
    if (!data) return 0;

    return data->channel_layout;
}

void QAudioCodecContext::setChannelLayout(uint64_t value)
{
    if (!data) return;

    data->channel_layout = value;
}

int QAudioCodecContext::getChannels() const
{
    if (!data) return 0;

    return data->channels;
}

void QAudioCodecContext::setChannels(int value)
{
    if (!data) return;

    data->channels = value;
}
