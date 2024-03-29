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
#include "media/base/video_decoder_config.h"
#include "media/base/decoder_buffer.h"

namespace media {
    // https://ffmpeg.org/doxygen/trunk/demux_decode_8c-example.html
    class FFmpegVideoDecoder {
    public:
        bool Open(const std::string& file_path);

        void Initialize(const VideoDecoderConfig& config);

        bool Decode(std::shared_ptr<DecoderBuffer> buffer);

        void Close();

        void Reset();

    private:
        enum class DecoderState {
            kUninitialized,
            kNormal,
            kDecodedFinished,
            kError
        };

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
