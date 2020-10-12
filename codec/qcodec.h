#ifndef QCODEC_H
#define QCODEC_H

#include <QObject>

#include <ffmpeg.h>

class QCodec : public QObject
{
    Q_OBJECT
public:
    QCodec(QObject *parent = nullptr);
    QCodec(AVCodec *codec);

    void clear();

    // SETTERS - GETTERS
    AVCodec *getData() const;

    QString getName() const;

    AVMediaType getType() const;

    QList<uint32_t> getTags() const;

protected:
    AVCodec *data;

};

#endif // QCODEC_H
