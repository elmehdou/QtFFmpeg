#ifndef QDECODER_H
#define QDECODER_H

#include <QObject>

#include "qcoder.h"

class QDecoder : public QCoder
{
    Q_OBJECT
public:
    QDecoder(AVStream *stream);
    QDecoder(Sptr<QStream> stream);
    QDecoder(AVCodecParameters* parameters, AVCodecID codecID);
    QDecoder(AVCodecParameters* parameters, const QString &name);

protected:
    AVCodec *findCoder(AVCodecID codecID) override;
    AVCodec *findCoder(const QString &name) override;
};

#endif // QDECODER_H
