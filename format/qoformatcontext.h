#ifndef QOFORMATCONTEXT_H
#define QOFORMATCONTEXT_H

#include "qformatcontext.h"


class QOFormatContext : public QFormatContext
{
public:
    QOFormatContext(const QString filename);

    bool allocate() override;

private:
};

#endif // QOFORMATCONTEXT_H
