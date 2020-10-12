#include "qoformatcontext.h"

#include <codec/context/qaudiocodeccontext.h>
#include <codec/context/qvideocodeccontext.h>

#include <codec/qvideocodec.h>

#include <QDebug>

QOFormatContext::QOFormatContext(const QString filename) : QFormatContext(filename)
{
    allocate();
}

QOFormatContext::~QOFormatContext()
{
    if (data && !(data->oformat->flags & AVFMT_NOFILE))
        avio_closep(&data->pb);
}

bool QOFormatContext::allocate()
{
    if (data) {
        qDebug() << "Format context must be cleared first.";
        return false;
    }

    int ret =  avformat_alloc_output_context2(&data, nullptr, nullptr, filename.toStdString().c_str());
    if (ret < 0) return false;

    return true;
}

int QOFormatContext::addStream(Sptr<QStream> inStream, Sptr<QDecoder> decoder, Sptr<QEncoder> encoder)
{
    if (!inStream) return -1;

    if (!decoder && !encoder) return -1;

    int ret = 0;

    AVCodec *codec = decoder->getCodec()->getData();
    if (encoder) codec = encoder->getCodec()->getData();

    // Create new output stream and set default value based on codec
    AVStream *stream = avformat_new_stream(data, codec);
    if (!stream) return -1;

    // Add stream to list
    Sptr<QStream> outStream = Sptr<QStream>::create(stream);
    streams.append(outStream);


    if (encoder){
        Sptr<QCodec> encoderCodec = encoder->getCodec();
        Sptr<QCodecContext> encoderContext = encoder->getContext();

        if (decoder->getContext()->getType() == AVMEDIA_TYPE_VIDEO || decoder->getContext()->getType() == AVMEDIA_TYPE_AUDIO){
            if (decoder->getContext()->getType() == AVMEDIA_TYPE_VIDEO){
                // Copy decoder context parameters into encoder one
                Sptr<QVideoCodecContext> encoderVideoCtx = encoderContext.dynamicCast<QVideoCodecContext>();
                Sptr<QVideoCodecContext> decoderVideoCtx = encoderContext.dynamicCast<QVideoCodecContext>();
                ret = encoderVideoCtx->copyParameters(decoderVideoCtx);
                if (ret < 0) return ret;

                // Check for codec pixel formats
                Sptr<QVideoCodec> encoderVideoCodec = encoder->getCodec().dynamicCast<QVideoCodec>();
                if (encoderVideoCodec)
                    if (encoderVideoCodec->getPixelFormats().count())
                        encoderVideoCtx->setPixelFormat(encoderVideoCodec->getPixelFormats().at(0));

            } else {
                // Copy decoder context parameters into encoder one
                Sptr<QAudioCodecContext> encoderAudioCtx = encoder->getContext().dynamicCast<QAudioCodecContext>();
                Sptr<QAudioCodecContext> decoderAudioCtx = decoder->getContext().dynamicCast<QAudioCodecContext>();
                ret = encoderAudioCtx->copyParameters(decoderAudioCtx);
                if (ret < 0) return ret;
            }

            // Some formats need global headers
            if (data->oformat->flags & AVFMT_GLOBALHEADER){
                encoderContext->setFlags(encoderContext->getFlags() | AV_CODEC_FLAG_GLOBAL_HEADER);
            }

            // Open encoder
            ret = encoder->open();
            if (ret < 0) return ret;

            // Copy encoder context parameters to output stream
            ret = outStream->copyParameters(encoderContext);
            if (ret < 0) return ret;
        }
    } else {
        // REMUXING
        // Copy input stream parameters to output stream
        ret = outStream->copyParameters(inStream);
        if (ret < 0) return ret;

        // IMPLEMENT CODEC TAG VERIFICATION
        qDebug() << "TAGS:" << getOutputCodecTags();
//        outStream->getCodecParameters()->codec_tag = 0;
//        data->oformat->codec_ta
    }

    return 0;
}

int QOFormatContext::openFile()
{
    int ret = 0;

    // Open output file
    if (!(data->oformat->flags & AVFMT_NOFILE)) {
        ret = avio_open(&data->pb, filename.toStdString().c_str(), AVIO_FLAG_WRITE);
        if (ret < 0) {
            qDebug() << "Could not open output file: " << filename;
            return ret;
        }
    }

    return 0;
}

int QOFormatContext::writeHeader()
{
    // Write header to opened file
    int ret = avformat_write_header(data, nullptr);
    if (ret < 0) {
        qDebug() << "Error occurred when writing header to output file: " << filename;
        return ret;
    }

    return 0;
}

void QOFormatContext::clearCodecTags(int index)
{
    if (index == -1) {
        for (Sptr<QStream> stream : streams){
            if (!stream->getCodecParameters()) continue;
            stream->getCodecParameters()->codec_tag = 0;
        }
    } else {
        for (Sptr<QStream> stream : streams){
            if (!stream->getCodecParameters()) continue;
            if (stream->getIndex() == index) {
                stream->getCodecParameters()->codec_tag = 0;
                break;
            }
        }
    }
}

void QOFormatContext::correctCodecTags()
{
    if (!streams.count()) return;

    QHash<AVCodecID, unsigned int> codecTags = getOutputCodecTags();

    for (Sptr<QStream> stream : streams){
        if (!stream->getCodecParameters()) continue;

        AVCodecID codecID = stream->getCodecParameters()->codec_id;
        unsigned int codecTag = stream->getCodecParameters()->codec_tag;

        unsigned int formatCodecTag = codecTags.value(codecID);
        if ( formatCodecTag != codecTag){
            stream->getCodecParameters()->codec_tag = formatCodecTag;
        }
    }
}

int QOFormatContext::write(AVPacket *packet)
{
    return av_interleaved_write_frame(data, packet);
}

int QOFormatContext::writeTrailer()
{
    return av_write_trailer(data);
}

QHash<AVCodecID, unsigned int> QOFormatContext::getOutputCodecTags() const
{
    QHash<AVCodecID, unsigned int> codecTags;

    if (!data->oformat) return codecTags;
    if (!data->oformat->codec_tag) return codecTags;

    int i = 1;
    const AVCodecTag *codecTag = data->oformat->codec_tag[0];
    while (true){
        qDebug() << codecTag->id << codecTag->tag;
        codecTags.insert(codecTag->id, codecTag->tag);
        codecTag = data->oformat->codec_tag[i];
        if (!codecTag) break;
        i++;
    }

    return codecTags;
}

void QOFormatContext::dump()
{
    av_dump_format(data, 0, nullptr, 1);
}
