//
// Created by wangrl2016 on 2023/7/19.
//

#include <gtest/gtest.h>
#include "media/base/decoder_buffer.h"

namespace media {
    TEST(DecoderBufferTest, Constructors) {
        std::shared_ptr<DecoderBuffer> buffer1(new DecoderBuffer(0));
        EXPECT_TRUE(buffer1->data());
        EXPECT_EQ(0u, buffer1->data_size());
        EXPECT_FALSE(buffer1->end_of_stream());

        const size_t kTestSize = 10;
        std::shared_ptr<DecoderBuffer> buffer2(new DecoderBuffer(kTestSize));
        ASSERT_TRUE(buffer2.get());
        EXPECT_EQ(kTestSize, buffer2->data_size());
    }

    TEST(DecoderBufferTest, CopyFrom) {
        const uint8_t kData[] = "hello";
        const size_t kDataSize = std::size(kData);

        std::shared_ptr<DecoderBuffer> buffer1(DecoderBuffer::CopyFrom(
                reinterpret_cast<const uint8_t*>(&kData), kDataSize));
        ASSERT_TRUE(buffer1.get());
        EXPECT_NE(kData, buffer1->data());
        EXPECT_EQ(buffer1->data_size(), kDataSize);
        EXPECT_EQ(0, memcmp(buffer1->data(), kData, kDataSize));

        std::shared_ptr<DecoderBuffer> buffer2(DecoderBuffer::CopyFrom(
                reinterpret_cast<const uint8_t*>(&kData), kDataSize,
                reinterpret_cast<const uint8_t*>(&kData), kDataSize));
        ASSERT_TRUE(buffer2.get());
        EXPECT_NE(kData, buffer2->data());
        EXPECT_EQ(buffer2->data_size(), kDataSize);
        EXPECT_EQ(0, memcmp(buffer2->data(), kData, kDataSize));
        EXPECT_NE(kData, buffer2->side_data());
        EXPECT_EQ(buffer2->side_data_size(), kDataSize);
        EXPECT_EQ(0, memcmp(buffer2->side_data(), kData, kDataSize));
        EXPECT_FALSE(buffer2->end_of_stream());
    }

    TEST(DecoderBufferTest, FromArray) {
        const uint8_t kData[] = "hello";
        const size_t kDataSize = std::size(kData);
        auto ptr = std::make_unique<uint8_t[]>(kDataSize);
        memcpy(ptr.get(), kData, kDataSize);

        std::shared_ptr<DecoderBuffer> buffer(
                DecoderBuffer::FromArray(std::move(ptr), kDataSize));
        ASSERT_TRUE(buffer.get());
        EXPECT_EQ(buffer->data_size(), kDataSize);
        EXPECT_EQ(0, memcmp(buffer->data(), kData, kDataSize));
        EXPECT_FALSE(buffer->end_of_stream());
    }

    TEST(DecoderBufferTest, ReadingWriting) {
        const char kData[] = "hello";
        const size_t kDataSize = std::size(kData);

        std::shared_ptr<DecoderBuffer> buffer(new DecoderBuffer(kDataSize));
        ASSERT_TRUE(buffer.get());

        uint8_t* data = buffer->data();
        ASSERT_TRUE(data);
        ASSERT_EQ(kDataSize, buffer->data_size());
        memcpy(data, kData, kDataSize);
        ASSERT_EQ(data, buffer->data());
        ASSERT_EQ(0, memcmp(buffer->data(), kData, kDataSize));
        EXPECT_FALSE(buffer->end_of_stream());
    }
}
