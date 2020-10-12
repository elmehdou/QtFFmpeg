#ifndef QENCODER_H
#define QENCODER_H

#include <QObject>

#include "qcoder.h"

class QEncoder : public QCoder
{
    Q_OBJECT
public:
    QEncoder(AVStream *stream);
    QEncoder(Sptr<QStream> stream);
    QEncoder(AVCodecParameters* parameters, AVCodecID codecID);
    QEncoder(AVCodecParameters* parameters, const QString &name);

protected:
    AVCodec *findCoder(AVCodecID codecID) override;
    AVCodec *findCoder(const QString &name) override;
};

#endif // QENCODER_H
