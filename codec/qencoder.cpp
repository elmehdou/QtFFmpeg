#include "qencoder.h"

#include <QDebug>

QEncoder::QEncoder(AVCodecID codecID) : QCoder()
{
    initialize(codecID);
}

QEncoder::QEncoder(const QString &codecName) : QCoder()
{
    initialize(codecName);
}

void QEncoder::initialize(AVCodecID codecID)
{
    if (codecID == AV_CODEC_ID_NONE) return;
    AVMediaType type = avcodec_get_type(codecID);

    switch (type) {
    case AVMEDIA_TYPE_VIDEO:
        codec = Sptr<QVideoCodec>::create(findCoder(codecID));
        context = Sptr<QVideoCodecContext>::create(codec);
        return;
    case AVMEDIA_TYPE_AUDIO:
        codec = Sptr<QAudioCodec>::create(findCoder(codecID));
        context = Sptr<QAudioCodecContext>::create(codec);
        return;
    default:
        codec = Sptr<QCodec>::create(findCoder(codecID));
        context = Sptr<QCodecContext>::create(codec);
    }
}

void QEncoder::initialize(const QString &name)
{
    if (name.isEmpty()) return;

    AVCodec *_codec = findCoder(name);
    AVMediaType type = _codec->type;

    switch (type) {
    case AVMEDIA_TYPE_VIDEO:
        codec = Sptr<QVideoCodec>::create(_codec);
        context = Sptr<QVideoCodecContext>::create(_codec);
        return;
    case AVMEDIA_TYPE_AUDIO:
        codec = Sptr<QAudioCodec>::create(_codec);
        context = Sptr<QAudioCodecContext>::create(_codec);
        return;
    default:
        codec = Sptr<QCodec>::create(_codec);
        context = Sptr<QCodecContext>::create(_codec);
        return;
    }
}

int QEncoder::encode(AVFrame *frame, std::function<void (AVPacket *)> onEncoded)
{
    if (!context->getData()) {
        qDebug() << "No codec context available";
        return -1;
    }

    int ret = avcodec_send_frame(context->getData(), frame);
    if (ret < 0) {
        qDebug() << "Could not send frame to encoder";
        return ret;
    }

    AVPacket *packet = av_packet_alloc();
    if (!packet) {
        qDebug() << "Could not allocate packet";
        return -1;
    }

    while ((ret = avcodec_receive_packet(context->getData(),  packet)) >= 0){
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) return 0;
        if (ret < 0) {
            qDebug() << "Error receiving packet from encoder.";
            return ret;
        }
        onEncoded(packet);

        av_packet_unref(packet);
    }

    return ret;
}

AVCodec *QEncoder::findCoder(AVCodecID codecID)
{
    return avcodec_find_encoder(codecID);
}

AVCodec *QEncoder::findCoder(const QString &name)
{
    return avcodec_find_encoder_by_name(name.toStdString().c_str());
}

