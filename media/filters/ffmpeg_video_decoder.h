//
// Created by wangrl2016 on 2023/7/14.
//

#ifndef CHARACTER_FFMPEG_VIDEO_DECODER_H
#define CHARACTER_FFMPEG_VIDEO_DECODER_H

#include <string>

extern "C" {
#include <libavformat/avformat.h>
};


namespace app {
    // https://ffmpeg.org/doxygen/trunk/demux_decode_8c-example.html
    class FFmpegVideoDecoder {
    public:
        bool Open(const std::string& file_path);

    private:

        AVFormatContext* format_context_;
        AVCodecContext* video_decode_context_, * audio_decode_context_;

    };
}

#endif //CHARACTER_FFMPEG_VIDEO_DECODER_H
