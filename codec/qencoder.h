#ifndef QENCODER_H
#define QENCODER_H

#include <QObject>
#include <functional>

#include "qcoder.h"

#include "qvideocodec.h"
#include "qaudiocodec.h"
#include <codec/context/qaudiocodeccontext.h>
#include <codec/context/qvideocodeccontext.h>

class QEncoder : public QCoder
{
    Q_OBJECT
public:
    QEncoder(AVCodecID codecID = AV_CODEC_ID_NONE);
    QEncoder(const QString &codecName = QString());

    void initialize(AVCodecID codecID);
    void initialize(const QString &name);

    int encode(AVFrame *frame, std::function<void(AVPacket*)> onEncoded);

protected:
    AVCodec *findCoder(AVCodecID codecID) override;
    AVCodec *findCoder(const QString &name) override;
};

#endif // QENCODER_H
