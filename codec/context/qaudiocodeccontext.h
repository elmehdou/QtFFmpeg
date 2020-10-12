#ifndef QAUDIOCODECCONTEXT_H
#define QAUDIOCODECCONTEXT_H

#include "qcodeccontext.h"



class QAudioCodecContext : public QCodecContext
{
    Q_OBJECT
public:
    QAudioCodecContext(AVCodecContext *context);
    QAudioCodecContext(AVCodecParameters *parameters);

    int copyParameters(Sptr<QAudioCodecContext> context);

    // SETTERS - GETTERS
    int getSampleRate() const;
    void setSampleRate(int value);

    uint64_t getChannelLayout() const;
    void setChannelLayout(uint64_t value);

    int getChannels() const;
    void setChannels(int value);
};

#endif // QAUDIOCODECCONTEXT_H
