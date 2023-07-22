//
// Created by wangrl2016 on 2023/7/17.
//

#ifndef CHARACTER_DECODER_BUFFER_H
#define CHARACTER_DECODER_BUFFER_H

#include <cstddef>
#include <memory>
#include <glog/logging.h>
#include "base/time/time_delta.h"

namespace media {
    // A specialized buffer for interfacing with audio / video decoders.
    //
    // NOTE: It is illegal to call any method when end_of_stream() is true.
    class DecoderBuffer {
    public:
        struct TimeInfo {
            TimeInfo();

            ~TimeInfo();

            TimeInfo(const TimeInfo&);

            TimeInfo& operator=(const TimeInfo&);

            // Presentation time of the frame
            base::TimeDelta timestamp;

            // Presentation duration of the frame.
            base::TimeDelta duration;
        };

        // Allocates buffer with |size| >= 0.
        explicit DecoderBuffer(size_t size);

        // Allocates a buffer of size |size| >= 0 and copies |data| into it. If |data|
        // is nullptr then |data_| is set to nullptr and |buffer_size_| to 0.
        DecoderBuffer(const uint8_t* data,
                      size_t size,
                      const uint8_t* side_data,
                      size_t side_data_size);

        DecoderBuffer(std::unique_ptr<uint8_t[]> data, size_t size);

        virtual ~DecoderBuffer();

        DecoderBuffer(const DecoderBuffer&) = delete;

        DecoderBuffer& operator=(const DecoderBuffer&) = delete;

        // Create a DecoderBuffer whose |data_| is copied from |data|. |data| must not
        // be nullptr and |size| >= 0.
        static std::shared_ptr<DecoderBuffer> CopyFrom(const uint8_t* data,
                                                       size_t size);

        // Create a DecoderBuffer whose |data_| is copied from |data| and |side_data_|
        // is copied from |side_data|. Data pointers must not be nullptr and sizes must
        // be >= 0.
        static std::shared_ptr<DecoderBuffer> CopyFrom(const uint8_t* data,
                                                       size_t size,
                                                       const uint8_t* side_data,
                                                       size_t side_data_size);

        // Create a DecoderBuffer where data() of |size| bytes resides within the heap
        // as byte array.
        // Ownership of |data| is transferred to the buffer.
        static std::shared_ptr<DecoderBuffer> FromArray(std::unique_ptr<uint8_t[]> data,
                                                        size_t size);

        // Create a DecoderBuffer indicating we've reached end of stream.
        //
        // Calling any method other than end_of_stream() on the resulting buffer
        // is disallowed.
        static std::shared_ptr<DecoderBuffer> CreateEOSBuffer();

        [[nodiscard]] const TimeInfo& time_info() const {
            DCHECK(!end_of_stream());
            return time_info_;
        }

        [[nodiscard]] base::TimeDelta timestamp() const {
            DCHECK(!end_of_stream());
            return time_info_.timestamp;
        }

        [[nodiscard]] base::TimeDelta duration() const {
            DCHECK(!end_of_stream());
            return time_info_.duration;
        }

        [[nodiscard]] uint8_t* data() {
            DCHECK(!end_of_stream());
            return data_.get();
        }

        [[nodiscard]] size_t data_size() const {
            DCHECK(!end_of_stream());
            return size_;
        }

        [[nodiscard]] const uint8_t* side_data() const {
            DCHECK(!end_of_stream());
            return side_data_.get();
        }

        [[nodiscard]] size_t side_data_size() const {
            DCHECK(!end_of_stream());
            return side_data_size_;
        }

        // If there's no data in this buffer, it represents end of stream.
        [[nodiscard]] bool end_of_stream() const { return !data_; }

        // Returns a human-readable string describing |*this|.
        std::string AsHumanReadableString(bool verbose = false) const;

        // Replaces any existing side data with data copied from |side_data|.
        void CopySideDataFrom(const uint8_t* side_data, size_t side_data_size);

    private:
        // Constructor helper method for memory allocations.
        void Initialize();

        TimeInfo time_info_;

        // Size of the encoded data.
        size_t size_;

        // Encoded data, if it is stored on the heap.
        std::unique_ptr<uint8_t[]> data_;

        size_t side_data_size_ = 0;
        std::unique_ptr<uint8_t[]> side_data_;
    };
}

#endif //CHARACTER_DECODER_BUFFER_H
