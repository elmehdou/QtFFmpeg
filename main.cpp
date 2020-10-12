#include <QCoreApplication>
#include <QDebug>

#include <format/qiformatcontext.h>
#include <format/qoformatcontext.h>

#include <codec/qdecoder.h>
#include <codec/qaudiocodec.h>
#include <codec/qvideocodec.h>

#include <codec/context/qaudiocodeccontext.h>
#include <codec/context/qvideocodeccontext.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // INPUT - Streams are found at contrsuction of the object
    QIFormatContext inFormatCtx("C:/Users/ElMehDou/Downloads/01.mkv");

    QOFormatContext outFormatCtx("C:/Users/ElMehDou/Downloads/test.mkv");
    outFormatCtx.allocate();

    // Find decoders and add streams to output
    QList<Sptr<QDecoder>> decoders;
    for (Sptr<QStream> stream : inFormatCtx.getStreams()){

        Sptr<QDecoder> decoder = Sptr<QDecoder>::create(stream);
        decoders << decoder;

        Sptr<QVideoCodec> videoCodec = decoder->getCodec().dynamicCast<QVideoCodec>();
        Sptr<QVideoCodecContext> videoCodecCtx = decoder->getContext().dynamicCast<QVideoCodecContext>();
        if (videoCodec && videoCodecCtx){
            videoCodecCtx->guessFramerate(inFormatCtx.getData(), stream->getData());
        }

        Sptr<QAudioCodec> audioCodec = decoder->getCodec().dynamicCast<QAudioCodec>();
        Sptr<QAudioCodecContext> audioCodecCtx = decoder->getContext().dynamicCast<QAudioCodecContext>();
        if (audioCodec && audioCodecCtx){
        }

        // Open decoder
        if (decoder->open() < 0){
            qDebug() << "Could not open decoder";
            continue;
        }

        // Adding stream to muxer
        outFormatCtx.addStream(stream, decoder);
    }

    inFormatCtx.dump();
    outFormatCtx.dump();


    return a.exec();
}
