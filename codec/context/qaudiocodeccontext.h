#ifndef QAUDIOCODECCONTEXT_H
#define QAUDIOCODECCONTEXT_H

#include "qcodeccontext.h"



class QAudioCodecContext : public QCodecContext
{
    Q_OBJECT
public:
    QAudioCodecContext(AVCodec *codec);
    QAudioCodecContext(Sptr<QCodec> codec);

    QAudioCodecContext(AVCodecContext *context);

    QAudioCodecContext(AVCodecParameters *parameters);

    int copyContext(Sptr<QAudioCodecContext> context);
    int copyContext(Sptr<QCodecContext> context) override;

    // SETTERS - GETTERS
    int getSampleRate() const;
    void setSampleRate(int value);

    uint64_t getChannelLayout() const;
    void setChannelLayout(uint64_t value);

    int getChannels() const;
    void setChannels(int value);
};

#endif // QAUDIOCODECCONTEXT_H
