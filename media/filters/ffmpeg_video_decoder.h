//
// Created by wangrl2016 on 2023/7/14.
//

#ifndef CHARACTER_FFMPEG_VIDEO_DECODER_H
#define CHARACTER_FFMPEG_VIDEO_DECODER_H

#include <string>

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}


namespace app {
    // https://ffmpeg.org/doxygen/trunk/demux_decode_8c-example.html
    class FFmpegVideoDecoder {
    public:
        bool Open(const std::string& file_path);

        bool Decode();

        void Close();

    private:
        bool OpenCodecContext(int* stream_index,
                              AVCodecContext** decoder_context,
                              enum AVMediaType type);

        bool DecodePacket(AVCodecContext* decoder);

        AVFormatContext* format_context_;
        AVCodecContext* video_decoder_context_, * audio_decoder_context_;
        AVFrame* frame_;
        AVPacket* packet_;

        int video_stream_index_, audio_stream_index_;

    };
}

#endif //CHARACTER_FFMPEG_VIDEO_DECODER_H
