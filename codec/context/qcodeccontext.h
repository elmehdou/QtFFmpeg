#ifndef QCODECCONTEXT_H
#define QCODECCONTEXT_H

class QCodecContext;

#include <QObject>

#include <ffmpeg.h>

#include <codec/qcodec.h>

#include <format/qstream.h>

class QCodecContext : public QObject
{
    Q_OBJECT
public:
    QCodecContext(QObject *parent = nullptr);

    QCodecContext(AVCodec *codec);
    QCodecContext(Sptr<QCodec> codec);

    QCodecContext(AVCodecContext *context);

    QCodecContext(AVCodecParameters *parameters);

    ~QCodecContext();
    void clear();

    bool allocate(AVCodec *codec);
    bool allocate(Sptr<QCodec> codec = nullptr);

    int copyParameters(Sptr<QStream> stream);
    int copyParameters(AVStream *stream);
    int copyParameters(AVCodecParameters *parameters);

    virtual int copyContext(Sptr<QCodecContext> context);

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
