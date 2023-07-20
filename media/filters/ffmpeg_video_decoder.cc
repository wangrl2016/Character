//
// Created by wangrl2016 on 2023/7/14.
//

#include <glog/logging.h>
#include "media/filters/ffmpeg_video_decoder.h"

namespace media {
    bool FFmpegVideoDecoder::Open(const std::string& file_path) {
        // Open input file, and allocate format context.
        if (avformat_open_input(&format_context_, file_path.c_str(), nullptr, nullptr) < 0) {
            LOG(ERROR) << "Could not open source file " << file_path;
            return false;
        }

        // Retrieve stream information.
        if (avformat_find_stream_info(format_context_, nullptr) < 0) {
            LOG(ERROR) << "Could not find stream information";
            return false;
        }

        if (OpenCodecContext(&video_stream_index_,
                             &video_decoder_context_,
                             AVMEDIA_TYPE_VIDEO)) {

        }

        if (OpenCodecContext(&audio_stream_index_,
                             &audio_decoder_context_,
                             AVMEDIA_TYPE_AUDIO)) {

        }

        // dump input information
        av_dump_format(format_context_, 0, file_path.c_str(), 0);

        return true;
    }

    bool FFmpegVideoDecoder::Decode() {
        while (av_read_frame(format_context_, packet_) >= 0) {
            if (packet_->stream_index == video_stream_index_) {

            } else if (packet_->stream_index == audio_stream_index_) {

            }
        }

        return true;
    }

    void FFmpegVideoDecoder::Close() {
        avcodec_free_context(&video_decoder_context_);
        avcodec_free_context(&audio_decoder_context_);
        avformat_close_input(&format_context_);

        av_packet_free(&packet_);
        av_frame_free(&frame_);
    }

    bool FFmpegVideoDecoder::OpenCodecContext(int* stream_index,
                                              AVCodecContext** decoder_context,
                                              enum AVMediaType type) {
        AVStream* stream;
        const AVCodec* decoder = nullptr;
        int index;
        int ret = av_find_best_stream(format_context_,
                                      type,
                                      -1,
                                      -1,
                                      nullptr,
                                      0);
        if (ret < 0) {
            LOG(ERROR) << "Could not find " << av_get_media_type_string(type)
                       << " stream in input file";
            return false;
        } else {
            index = ret;
            stream = format_context_->streams[index];

            // find decoder for the stream
            decoder = avcodec_find_decoder(stream->codecpar->codec_id);
            if (!decoder) {
                LOG(ERROR) << "Failed to find " << av_get_media_type_string(type)
                           << " codec";
                return false;
            }

            // Allocate a codec context for the decoder.
            *decoder_context = avcodec_alloc_context3(decoder);
            if (!*decoder_context) {
                LOG(ERROR) << "Failed to allocate the " << av_get_media_type_string(type)
                           << " codec context";
                return false;
            }

            // Copy codec parameters from input stream to output codec context.
            if ((ret = avcodec_parameters_to_context(*decoder_context, stream->codecpar)) < 0) {
                LOG(ERROR) << "Failed to copy " << av_get_media_type_string(type)
                           << " codec parameters to decoder context";
                return false;
            }

            // Init the decoders.
            if ((ret = avcodec_open2(*decoder_context, decoder, nullptr)) < 0) {
                LOG(ERROR) << "Failed to open " << av_get_media_type_string(type)
                           << " codec";
                return false;
            }
            *stream_index = index;
        }

        frame_ = av_frame_alloc();
        if (!frame_) {
            LOG(ERROR) << "Could not allocate frame";
            return false;
        }

        packet_ = av_packet_alloc();
        if (!packet_) {
            LOG(ERROR) << "Could not allocate packet";
            return false;
        }
        return true;
    }

    bool FFmpegVideoDecoder::DecodePacket(AVCodecContext* decoder) {
        // submit the packet to the decoder
        int ret = avcodec_send_packet(decoder, packet_);
        if (ret < 0) {
            LOG(ERROR) << "Error submitting a packet for decoding";
            return false;
        }

        // get all the available frames from the decoder
        while (ret >= 0) {
            ret = avcodec_receive_frame(decoder, frame_);
            if (ret < 0) {
                // Those two return values are special and mean there is no output
                // frame available, but there were no errors during decoding.
                if (ret == AVERROR_EOF || ret == AVERROR(EAGAIN))
                    return true;
                LOG(ERROR) << "Error during decoding";
                return false;
            }

            // Write the frame data to output file
            if (decoder->codec->type == AVMEDIA_TYPE_VIDEO) {

            } else if (decoder->codec->type == AVMEDIA_TYPE_AUDIO) {

            }

            av_frame_unref(frame_);
            if (ret < 0)
                return false;
        }
        return true;
    }
}
