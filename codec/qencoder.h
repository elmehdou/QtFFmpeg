#ifndef QENCODER_H
#define QENCODER_H

#include <QObject>

#include "qcoder.h"

class QEncoder : public QCoder
{
    Q_OBJECT
public:
    QEncoder(AVStream *stream, AVCodecID codecID = AV_CODEC_ID_NONE);
    QEncoder(AVStream *stream, const QString &codecName = QString());

    QEncoder(Sptr<QStream> stream, AVCodecID codecID = AV_CODEC_ID_NONE);
    QEncoder(Sptr<QStream> stream, const QString &codecName = QString());

    QEncoder(AVCodecParameters* parameters, AVCodecID codecID = AV_CODEC_ID_NONE);
    QEncoder(AVCodecParameters* parameters, const QString &codecName = QString());

protected:
    AVCodec *findCoder(AVCodecID codecID) override;
    AVCodec *findCoder(const QString &name) override;
};

#endif // QENCODER_H
