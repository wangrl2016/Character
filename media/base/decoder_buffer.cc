//
// Created by wangrl2016 on 2023/7/17.
//

#include "media/base/decoder_buffer.h"

#include <memory>

namespace media {
    DecoderBuffer::TimeInfo::TimeInfo() = default;

    DecoderBuffer::TimeInfo::~TimeInfo() = default;

    DecoderBuffer::TimeInfo::TimeInfo(const TimeInfo&) = default;

    DecoderBuffer::TimeInfo& DecoderBuffer::TimeInfo::operator=(const TimeInfo&) = default;

    DecoderBuffer::DecoderBuffer(size_t size) :
            size_(size), side_data_size_(0) {
        Initialize();
    }

    DecoderBuffer::DecoderBuffer(const uint8_t* data,
                                 size_t size,
                                 const uint8_t* side_data,
                                 size_t side_data_size) :
            size_(size),
            side_data_size_(side_data_size) {
        if (!data) {
            CHECK_EQ(size_, 0u);
            CHECK(!side_data);
            return;
        }

        Initialize();

        memcpy(data_.get(), data, size_);

        if (!side_data) {
            CHECK_EQ(side_data_size, 0u);
            return;
        }

        DCHECK_GT(side_data_size_, 0u);
        memcpy(side_data_.get(), side_data, side_data_size_);
    }

    DecoderBuffer::DecoderBuffer(std::unique_ptr<uint8_t[]> data, size_t size) :
            data_(std::move(data)), size_(size) {
    }

    DecoderBuffer::~DecoderBuffer() {
        data_.reset();
        side_data_.reset();
    }

    std::shared_ptr<DecoderBuffer> DecoderBuffer::CopyFrom(const uint8_t* data, size_t size) {
        // If you hit this CHECK you likely have a bug in a de-muxer. Go fix it.
        CHECK(data);
        return std::make_unique<DecoderBuffer>(data, size, nullptr, 0);
    }

    std::shared_ptr<DecoderBuffer> DecoderBuffer::CopyFrom(const uint8_t* data,
                                                           size_t size,
                                                           const uint8_t* side_data,
                                                           size_t side_data_size) {
        CHECK(data);
        CHECK(side_data);
        return std::make_unique<DecoderBuffer>(data,
                                               size,
                                               side_data,
                                               side_data_size);
    }

    std::shared_ptr<DecoderBuffer> DecoderBuffer::FromArray(std::unique_ptr<uint8_t[]> data,
                                                            size_t size) {
        CHECK(data);
        return std::make_unique<DecoderBuffer>(std::move(data), size);
    }

    std::shared_ptr<DecoderBuffer> DecoderBuffer::CreateEOSBuffer() {
        return std::make_shared<DecoderBuffer>(nullptr, 0, nullptr, 0);
    }

    void DecoderBuffer::Initialize() {
        data_.reset(new uint8_t[size_]);
        if (side_data_size_ > 0)
            side_data_.reset(new uint8_t[side_data_size_]);
    }
}
