#ifndef QIFORMATCONTEXT_H
#define QIFORMATCONTEXT_H

#include "qformatcontext.h"


class QIFormatContext : public QFormatContext
{
public:
    QIFormatContext(const QString filename);

    bool allocate() override;

    int openInput(AVInputFormat *inputFormat = nullptr, AVDictionary **options = nullptr);

    int findStreamInfo(AVDictionary **options = nullptr);

    void dump() override;
};

#endif // QIFORMATCONTEXT_H
