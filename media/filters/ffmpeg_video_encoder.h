//
// Created by wangrl2016 on 2023/6/29.
//

#ifndef CHARACTER_FFMPEG_VIDEO_ENCODER_H
#define CHARACTER_FFMPEG_VIDEO_ENCODER_H

#include <string>

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswresample/swresample.h>
#include <libswscale/swscale.h>
#include <libavutil/avutil.h>
};

namespace media {
    // a wrapper around a single output AVStream
    typedef struct OutputStream {
        AVStream* stream;
        AVCodecContext* encoder;

        // pts of the next frame that will be generated
        int64_t next_pts;
        int samples_count;

        AVFrame* frame;
        AVFrame* temp_frame;

        AVPacket* temp_packet;

        float t, cr, cr2;

        struct SwsContext* sws_context;
        struct SwrContext* swr_context;
    } OutputStream;

    class FFmpegVideoEncoder {
    public:
        FFmpegVideoEncoder();

        ~FFmpegVideoEncoder();

        bool Open(std::string file_path);

    private:
        bool AddStream(OutputStream* stream, enum AVCodecID codec_id);

        bool OpenVideo(AVDictionary* opt_arg);

        bool OpenAudio(AVDictionary* opt_arg);

        AVFormatContext* output_format_context_;
        OutputStream video_stream_, audio_stream_;
        const AVCodec* video_codec_, * audio_codec_;
        bool have_video_, have_audio_;
        bool encode_video, encode_audio_;
    };
}

#endif //CHARACTER_FFMPEG_VIDEO_ENCODER_H
