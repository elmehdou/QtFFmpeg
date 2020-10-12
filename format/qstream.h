#ifndef QSTREAM_H
#define QSTREAM_H

class QStream;

#include <QObject>

#include <ffmpeg.h>

#include <codec/context/qcodeccontext.h>

class QStream : public QObject
{
    Q_OBJECT
public:
    QStream(AVStream *stream);

    int copyParameters(AVStream *stream);
    int copyParameters(Sptr<QStream> stream);
    int copyParameters(AVCodecContext *stream);
    int copyParameters(Sptr<QCodecContext> stream);

    // SETTERS - GETTERS
    AVStream *getData() const;

    AVCodecParameters *getCodecParameters() const;

private:
    AVStream *data;
};

#endif // QSTREAM_H
