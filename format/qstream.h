#ifndef QSTREAM_H
#define QSTREAM_H

#include <QObject>

#include <ffmpeg.h>

class QStream : public QObject
{
    Q_OBJECT
public:
    QStream(AVStream *stream);

    AVStream *getData() const;

    AVCodecParameters *getCodecParameters() const;

private:
    AVStream *data;
};

#endif // QSTREAM_H
