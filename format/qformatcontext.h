#ifndef QFORMATCONTEXT_H
#define QFORMATCONTEXT_H

#include <QObject>

#include <ffmpeg.h>

#include "qstream.h"

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

protected:
    QString filename;
    AVFormatContext *data;
    QList<Sptr<QStream>> streams;
};

#endif // QFORMATCONTEXT_H
