#ifndef QOFORMATCONTEXT_H
#define QOFORMATCONTEXT_H

#include "qformatcontext.h"

#include <codec/qdecoder.h>
#include <codec/qencoder.h>


class QOFormatContext : public QFormatContext
{
public:
    QOFormatContext(const QString filename);
    ~QOFormatContext();

    bool allocate() override;

    int addStream(Sptr<QStream> inStream, Sptr<QDecoder> decoder, Sptr<QEncoder> encoder = nullptr);

    int openFile();

    int writeHeader();

    void clearCodecTags(int index = -1);
    void correctCodecTags();

    int write(AVPacket *packet);

    int writeTrailer();

    void dump() override;

    // SETTERS - GETTERS
    QHash<AVCodecID, unsigned int> getOutputCodecTags() const;
};

#endif // QOFORMATCONTEXT_H
