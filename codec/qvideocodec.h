#ifndef QVIDEOCODEC_H
#define QVIDEOCODEC_H

#include "qcodec.h"



class QVideoCodec : public QCodec
{
    Q_OBJECT
public:
    QVideoCodec(AVCodec *codec);

    // SETTERS - GETTERS
    QList<AVPixelFormat> getPixelFormats() const;
};

#endif // QVIDEOCODEC_H
