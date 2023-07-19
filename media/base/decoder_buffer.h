//
// Created by wangrl2016 on 2023/7/17.
//

#ifndef CHARACTER_DECODER_BUFFER_H
#define CHARACTER_DECODER_BUFFER_H

#include <cstddef>
#include <memory>
#include <glog/logging.h>

namespace media {
    // A specialized buffer for interfacing with audio / video decoders.
    //
    // NOTE: It is illegal to call any method when end_of_stream() is true.
    class DecoderBuffer {
    public:
        // Allocates buffer with |size| >= 0.
        explicit DecoderBuffer(size_t size);

        DecoderBuffer(const uint8_t* data,
                      size_t size,
                      const uint8_t* side_data,
                      size_t side_data_size);

        DecoderBuffer(const DecoderBuffer&) = delete;

        DecoderBuffer& operator=(const DecoderBuffer&) = delete;

        // Create a DecoderBuffer whose |data_| is copied from |data|. |data| must not
        // be nullptr and |size| >= 0.
        static std::shared_ptr<DecoderBuffer> CopyFrom(const uint8_t* data,
                                                       size_t size);

        const uint8_t* data() const {
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


    protected:

        // Encoded data, if it is stored on the heap.
        std::unique_ptr<uint8_t> data_;

    private:
        // Constructor helper method for memory allocations.
        void Initialize();

        // Size of the encoded data.
        size_t size_;

        size_t side_data_size_ = 0;
        std::unique_ptr<uint8_t[]> side_data_;

    };
}

#endif //CHARACTER_DECODER_BUFFER_H
