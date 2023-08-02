//
// Created by wangrl2016 on 2023/8/2.
//

#ifndef CHARACTER_VIDEO_DECODER_CONFIG_H
#define CHARACTER_VIDEO_DECODER_CONFIG_H

extern "C" {
#include <libavcodec/avcodec.h>
};

#include "media/base/video_aspect_ratio.h"

namespace media {
    // Describes the content of the video stream, as described by the media container
    // (or otherwise determined by the demuxer).
    class VideoDecoderConfig {
    public:
        enum class AlphaMode { kHasAlpha, kIsOpaque };

        // Constructs an uninitialized object. Clients should call Initialize() with
        // appropriate values before using.
        VideoDecoderConfig() = default;

    private:
        AVCodecID video_codec_ = AV_CODEC_ID_NONE;

        AlphaMode alpha_mode_ = AlphaMode::kIsOpaque;

        VideoAspectRatio aspect_ratio_;
    };
}


#endif //CHARACTER_VIDEO_DECODER_CONFIG_H
