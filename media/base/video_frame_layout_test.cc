//
// Created by wangrl2016 on 2023/8/10.
//

#include <glog/logging.h>
#include <gtest/gtest.h>
#include "core/geometry/size.h"
#include "media/base/color_plane_layout.h"
#include "media/base/video_frame_layout.h"
#include "media/base/video_types.h"
#include "media/base/video_frame.h"

namespace media {
   std::vector<ColorPlaneLayout> CreatePlanes(const std::vector<int32_t>& strides,
                                              const std::vector<size_t>& offsets,
                                              const std::vector<size_t>& sizes) {
       LOG_ASSERT(strides.size() == offsets.size());
       std::vector<ColorPlaneLayout> planes(strides.size());
       for (size_t i = 0; i < strides.size(); i++) {
           planes[i].stride = strides[i];
           planes[i].offset = offsets[i];
           planes[i].size = sizes[i];
       }
       return planes;
   }

   TEST(VideoFrameLayout, CreateI420) {
       core::Size coded_size = core::Size(320, 180);
       auto layout = VideoFrameLayout::Create(kPixelFormatI420, coded_size);

       auto num_of_planes = VideoFrame::NumPlanes(kPixelFormatI420);
        EXPECT_EQ(layout->format(), kPixelFormatI420);
        EXPECT_EQ(layout->coded_size(), coded_size);
        EXPECT_EQ(layout->num_planes(), num_of_planes);
        for (size_t i = 0; i < num_of_planes; i++) {
            EXPECT_EQ(layout->planes()[i].stride, 0);
            EXPECT_EQ(layout->planes()[i].offset, 0u);
            EXPECT_EQ(layout->planes()[i].size, 0u);
        }
   }

   TEST(VideoFrameLayout, CreateWithStrides) {
       core::Size coded_size = core::Size(320, 180);
       std::vector<int32_t> strides = {384, 192, 192};
       auto layout = VideoFrameLayout::CreateWithStrides(kPixelFormatI420,
                                                         coded_size,
                                                         strides);

        ASSERT_EQ(layout->format(), kPixelFormatI420);
        ASSERT_EQ(layout->coded_size(), coded_size);
        ASSERT_EQ(layout->num_planes(), 3u);
        for (size_t i = 0; i < 3; i++) {
            EXPECT_EQ(layout->planes()[i].stride, strides[i]);
            EXPECT_EQ(layout->planes()[i].offset, 0u);
            EXPECT_EQ(layout->planes()[i].size, 0u);
        }
   }

    TEST(VideoFrameLayout, CreateWithPlanes) {
       core::Size coded_size = core::Size(320, 180);
       std::vector<int32_t> strides = {384, 192, 192};
       std::vector<size_t> offsets = {0, 0, 200};
       std::vector<size_t> sizes = {200, 100, 100};
       auto layout = VideoFrameLayout::CreateWithPlanes(
               kPixelFormatI420,
               coded_size,
               CreatePlanes(strides, offsets, sizes));

        EXPECT_EQ(layout->format(), kPixelFormatI420);
        EXPECT_EQ(layout->coded_size(), coded_size);
        EXPECT_EQ(layout->num_planes(), 3u);
        for (size_t i = 0; i < 3; i++) {
            EXPECT_EQ(layout->planes()[i].stride, strides[i]);
            EXPECT_EQ(layout->planes()[i].offset, offsets[i]);
            EXPECT_EQ(layout->planes()[i].size, sizes[i]);
        }
   }

   TEST(VideoFrameLayout, CopyConstructor) {
       core::Size coded_size = core::Size(320, 180);
       std::vector<int32_t> strides = {384, 192, 192};
       std::vector<size_t> offsets = {0, 0, 200};
       std::vector<size_t> sizes = {200, 100, 100};
   }
}
