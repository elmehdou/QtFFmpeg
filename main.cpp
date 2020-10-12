#include <QCoreApplication>
#include <QDebug>

#include <format/qiformatcontext.h>

#include <codec/qdecoder.h>
#include <codec/qaudiocodec.h>
#include <codec/qvideocodec.h>

#include <codec/context/qaudiocodeccontext.h>
#include <codec/context/qvideocodeccontext.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // INPUT - Streams are found at contrsuction of the object
    QIFormatContext inFormatCtx("C:/Users/ElMehDou/Downloads/test.mp4");

    // Find decoders
    QList<Sptr<QDecoder>> decoders;
    for (Sptr<QStream> stream : inFormatCtx.getStreams()){
        Sptr<QDecoder> decoder = Sptr<QDecoder>::create(stream);
        decoders << decoder;

        Sptr<QVideoCodec> videoCodec = decoder->getCodec().dynamicCast<QVideoCodec>();
        Sptr<QVideoCodecContext> videoCodecCtx = decoder->getContext().dynamicCast<QVideoCodecContext>();
        if (videoCodec && videoCodecCtx){
            qDebug() << "[ Video decoder ]";
            qDebug() << videoCodec->getName();
            qDebug() << videoCodec->getTags();
            qDebug() << videoCodec->getPixelFormats();
            qDebug() << videoCodecCtx->getPixelFormat();
            continue;
        }

        Sptr<QAudioCodec> audioCodec = decoder->getCodec().dynamicCast<QAudioCodec>();
        Sptr<QAudioCodecContext> audioCodecCtx = decoder->getContext().dynamicCast<QAudioCodecContext>();
        if (audioCodec && audioCodecCtx){
            qDebug() << "[ Audio decoder ]";
            qDebug() << audioCodec->getName();
            qDebug() << audioCodec->getTags();
            qDebug() << audioCodec->getSampleFormats();
            qDebug() << audioCodecCtx->getChannelLayout();
            continue;
        }
    }

    return a.exec();
}
