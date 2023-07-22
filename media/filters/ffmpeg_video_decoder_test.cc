//
// Created by wangrl2016 on 2023/7/17.
//

#include <gtest/gtest.h>
#include "core/geometry/size.h"
#include "media/base/video_frame.h"
#include "media/base/decoder_buffer.h"
#include "media/filters/ffmpeg_video_decoder.h"

namespace media {
    static const core::Size kCodedSize(320, 240);

    class FFmpegVideoDecoderTest : public testing::Test {
    public:
        typedef std::vector<std::shared_ptr<DecoderBuffer>> InputBuffers;
        typedef std::vector<std::shared_ptr<VideoFrame>> OutputFrames;

        FFmpegVideoDecoderTest() :
                decoder_(std::make_unique<FFmpegVideoDecoder>()) {
            // Initialize various test buffers.
            frame_buffer_ = std::make_unique<uint8_t[]>(kCodedSize.GetArea());
            end_of_stream_buffer_ = DecoderBuffer::CreateEOSBuffer();
        }


    private:

        std::unique_ptr<FFmpegVideoDecoder> decoder_;

        // Various buffers for testing.
        std::unique_ptr<uint8_t[]> frame_buffer_;
        std::shared_ptr<DecoderBuffer> end_of_stream_buffer_;
        std::shared_ptr<DecoderBuffer> i_frame_buffer_;
        std::shared_ptr<DecoderBuffer> corrupt_i_frame_buffer_;

        OutputFrames output_frames_;
    };
}
