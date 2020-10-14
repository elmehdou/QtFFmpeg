#include "qdecoder.h"

#include <QDebug>

QDecoder::QDecoder(Sptr<QStream> stream) : QDecoder(stream->getData())
{
}

QDecoder::QDecoder(AVStream *stream) : QCoder()
{
    initialize(stream->codecpar);
}

QDecoder::QDecoder(AVCodecParameters *parameters) : QCoder()
{
    initialize(parameters);
}

void QDecoder::initialize(AVCodecParameters *parameters)
{
    if (!parameters) return;

    switch (parameters->codec_type) {
    case AVMEDIA_TYPE_VIDEO:
        codec = Sptr<QVideoCodec>::create(findCoder(parameters->codec_id));
        context = Sptr<QVideoCodecContext>::create(parameters);
        return;
    case AVMEDIA_TYPE_AUDIO:
        codec = Sptr<QAudioCodec>::create(findCoder(parameters->codec_id));
        context = Sptr<QAudioCodecContext>::create(parameters);
        return;
    default:
        codec = Sptr<QCodec>::create(findCoder(parameters->codec_id));
        context = Sptr<QCodecContext>::create(parameters);
    }
}

int QDecoder::decode(AVPacket *packet, std::function<void (AVFrame *)> onDecoded)
{
    if (!context->getData()) {
        qDebug() << "No codec context available";
        return -1;
    }

    int ret = avcodec_send_packet(context->getData(), packet);
    if (ret < 0) {
        qDebug() << "Could not send packet to decoder";
        return ret;
    }

    AVFrame *frame = av_frame_alloc();
    if (!frame) {
        qDebug() << "Could not allocate frame";
        return -1;
    }

    while ((ret = avcodec_receive_frame(context->getData(),  frame)) >= 0){
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) return 0;
        if (ret < 0) {
            qDebug() << "Error receiving frame from decoder.";
            return ret;
        }
        onDecoded(frame);

        av_frame_unref(frame);
    }

    return ret;
}

AVCodec *QDecoder::findCoder(AVCodecID codecID)
{
    return avcodec_find_decoder(codecID);
}

AVCodec *QDecoder::findCoder(const QString &name)
{
    return avcodec_find_decoder_by_name(name.toStdString().c_str());
}
