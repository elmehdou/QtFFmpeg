#ifndef QAUDIOCODEC_H
#define QAUDIOCODEC_H

#include "qcodec.h"



class QAudioCodec : public QCodec
{
    Q_OBJECT
public:
    QAudioCodec(AVCodec *codec);

    // SETTERS - GETTERS
    QList<AVSampleFormat> getSampleFormats() const;
};

#endif // QAUDIOCODEC_H
