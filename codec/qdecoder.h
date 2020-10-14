#ifndef QDECODER_H
#define QDECODER_H

#include <QObject>
#include <functional>

#include "qcoder.h"

#include "qvideocodec.h"
#include "qaudiocodec.h"
#include <codec/context/qaudiocodeccontext.h>
#include <codec/context/qvideocodeccontext.h>

class QDecoder : public QCoder
{
    Q_OBJECT
public:
    QDecoder(AVStream *stream);

    QDecoder(Sptr<QStream> stream);

    QDecoder(AVCodecParameters* parameters);

    void initialize(AVCodecParameters *parameters);
    void initializeCoder(AVCodecParameters *parameters, const QString &name);

    int decode(AVPacket *packet, std::function<void(AVFrame*)> onDecoded);

protected:
    AVCodec *findCoder(AVCodecID codecID) override;
    AVCodec *findCoder(const QString &name) override;
};

#endif // QDECODER_H
