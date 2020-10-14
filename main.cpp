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
    QIFormatContext inFormatCtx("C:/Users/ElMehDou/Downloads/test.mp4");

    QOFormatContext outFormatCtx("C:/Users/ElMehDou/Downloads/test.mkv");

    // Find decoders and add streams to output
    QHash<Sptr<QStream>, Sptr<QDecoder>> decodersHash;
    QHash<Sptr<QStream>, Sptr<QEncoder>> encodersHash;

    for (Sptr<QStream> stream : inFormatCtx.getStreams()){

        Sptr<QDecoder> decoder = Sptr<QDecoder>::create(stream);
        decodersHash.insert(stream, decoder);

        // Open decoder
        if (decoder->open() < 0){
            qDebug() << "Could not open decoder";
            continue;
        }

        Sptr<QVideoCodec> videoCodec = decoder->getCodec().dynamicCast<QVideoCodec>();
        Sptr<QVideoCodecContext> videoCodecCtx = decoder->getContext().dynamicCast<QVideoCodecContext>();
        if (videoCodec && videoCodecCtx){
            videoCodecCtx->guessFramerate(inFormatCtx.getData(), stream->getData());

            // Settings encoders
            Sptr<QEncoder> videoEncoder = Sptr<QEncoder>::create("libx265");
            if (videoEncoder->getCodec()){
                encodersHash.insert(stream, videoEncoder);
                videoEncoder->getContext()->copyContext(videoCodecCtx);
                Sptr<QVideoCodec> videoEncoderCodec = videoEncoder->getCodec().dynamicCast<QVideoCodec>();

                // Adding stream to muxer
                outFormatCtx.addStream(stream, decoder, videoEncoder);
                continue;
            }
        }

        Sptr<QAudioCodec> audioCodec = decoder->getCodec().dynamicCast<QAudioCodec>();
        Sptr<QAudioCodecContext> audioCodecCtx = decoder->getContext().dynamicCast<QAudioCodecContext>();
        if (audioCodec && audioCodecCtx){
        }


        // Adding stream to muxer
        outFormatCtx.addStream(stream, decoder);
    }

    inFormatCtx.dump();

    // Correct output stream code tags before writing
    outFormatCtx.clearCodecTags();
    outFormatCtx.dump();

    if (outFormatCtx.openFile() < 0) return -1;
    if (outFormatCtx.writeHeader() < 0) return -2;

    AVPacket *packet = av_packet_alloc();
    if (!packet) return -3;
    av_init_packet(packet);

    // Transcoding loop
    int ret = 0;
    while ((ret = inFormatCtx.read(packet)) >= 0){

        Sptr<QStream> inStream = inFormatCtx.getStream(packet->stream_index);
        Sptr<QStream> outStream = outFormatCtx.getStream(packet->stream_index);
        if (!inStream || !outStream) {
            av_packet_unref(packet);
            continue;
        }

        av_packet_rescale_ts(packet,
                             inStream->getTimeBase(),
                             outStream->getTimeBase());

        Sptr<QEncoder> encoder = encodersHash.value(inStream);
        if (encoder){
            Sptr<QDecoder> decoder = decodersHash.value(inStream);
            if (!decoder) {
                qDebug() << "No decoder found cannot rencode stream. Exiting.";
                return -4;
            }
            ret = decoder->decode(packet, [&](AVFrame *frame){
                encoder->encode(frame, [&](AVPacket *encodedPacket){
                    outFormatCtx.write(encodedPacket);
                });
            });
            if (ret < 0) break;

        } else {
            ret = outFormatCtx.write(packet);
            if (ret < 0) {
                qDebug() << "Could not write to output. Exiting.";
                return -5;
            }
        }

        av_packet_unref(packet);
    }

    outFormatCtx.writeTrailer();

    return a.exec();
}
