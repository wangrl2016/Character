//
// Created by wangrl2016 on 2023/6/29.
//

#include <glog/logging.h>
#include "media/filters/ffmpeg_video_encoder.h"

namespace media {
    FFmpegVideoEncoder::FFmpegVideoEncoder() {

    }

    FFmpegVideoEncoder::~FFmpegVideoEncoder() {

    }

    bool FFmpegVideoEncoder::Open(std::string file_path) {
        // allocate the output media context
        avformat_alloc_output_context2(&output_format_context_,
                                       nullptr,
                                       nullptr,
                                       file_path.c_str());
        if (!output_format_context_) {
            LOG(ERROR) << "Could not deduce output format from file extension: using MPEG.";
            avformat_alloc_output_context2(&output_format_context_,
                                           nullptr,
                                           "mpeg",
                                           file_path.c_str());
        }
        if (!output_format_context_)
            return false;

        auto fmt = output_format_context_->oformat;


        // Add the audio and video streams using the default format codecs
        // and initialize the codecs.
        if (fmt->video_codec != AV_CODEC_ID_NONE) {
            // AddStream(&video_stream_, output_format_context_, &video_codec_, fmt->audio_codec);
        }

    }
}
