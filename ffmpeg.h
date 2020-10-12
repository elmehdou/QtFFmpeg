#ifndef FFMPEG_H
#define FFMPEG_H

#include <QSharedPointer>

template <typename T>
using Sptr = QSharedPointer<T>;

extern "C" {
#include <libavformat/avformat.h>
#include <libavformat/avio.h>
#include <libavcodec/avcodec.h>
#include <libavutil/avutil.h>
#include <libavutil/opt.h>
}
#endif // FFMPEG_H
