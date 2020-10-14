#ifndef QCODER_H
#define QCODER_H

#include <QObject>

#include "qcodec.h"

#include <codec/context/qcodeccontext.h>

class QCoder : public QObject
{
    Q_OBJECT
public:
    QCoder();

    Sptr<QCodec> getCodec() const;

    Sptr<QCodecContext> getContext() const;

    virtual AVCodec *findCoder(AVCodecID codecID) = 0;
    virtual AVCodec *findCoder(const QString &name) = 0;

    int open(AVDictionary **options = 0);

protected:
    Sptr<QCodec> codec;
    Sptr<QCodecContext> context;
};

#endif // QCODER_H
