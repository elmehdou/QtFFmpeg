#ifndef QFORMATCONTEXT_H
#define QFORMATCONTEXT_H

#include <QObject>

#include <ffmpeg.h>

#include "qstream.h"

typedef struct AVCodecTag {
    enum AVCodecID id;
    unsigned int tag;
} AVCodecTag;

class QFormatContext : public QObject
{
    Q_OBJECT
public:
    QFormatContext(const QString &filename);
    ~QFormatContext();
    void clear();

    virtual bool allocate() = 0;

    virtual void dump() = 0;

    // SETTERS - GETTERS
    QString getFilename() const;

    AVFormatContext *getData() const;

    QList<Sptr<QStream>> getStreams() const;

    Sptr<QStream> getStream(int index) const;

protected:
    QString filename;
    AVFormatContext *data;
    QList<Sptr<QStream>> streams;
};

#endif // QFORMATCONTEXT_H
