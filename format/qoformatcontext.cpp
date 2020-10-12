#include "qoformatcontext.h"

QOFormatContext::QOFormatContext(const QString filename) : QFormatContext(filename)
{

}

bool QOFormatContext::allocate()
{
    clear();

    int ret =  avformat_alloc_output_context2(&data, nullptr, nullptr, filename.toStdString().c_str());
    if (ret < 0) return false;

    return true;
}
