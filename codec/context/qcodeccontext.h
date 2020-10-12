#ifndef QCODECCONTEXT_H
#define QCODECCONTEXT_H

#include <QObject>

#include <ffmpeg.h>

#include <codec/qcodec.h>

#include <format/qstream.h>

class QCodecContext : public QObject
{
    Q_OBJECT
public:
    QCodecContext(QObject *parent = nullptr);
    QCodecContext(AVCodecContext *context);
    QCodecContext(AVCodecParameters *parameters);

    ~QCodecContext();
    void clear();

    bool allocate(Sptr<QCodec> codec = nullptr);

    int copyParameters(QStream *stream);
    int copyParameters(AVStream *stream);
    int copyParameters(AVCodecParameters *parameters);

    // SETTERS - GETTERS
    AVCodecContext *getData() const;

    AVCodecID getID() const;

    AVMediaType getType() const;

    AVRational getTimeBase() const;
    void setTimeBase(AVRational value);
    void setTimeBase(int numerator, int denominator);

    uint32_t getCodecTag() const;
    void setCodecTag(uint32_t value);

    int getFlags() const;
    void setFlags(int value);

protected:
    AVCodecContext *data;

};

#endif // QCODECCONTEXT_H
