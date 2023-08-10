//
// Created by wangrl2016 on 2023/8/10.
//

#include <glog/logging.h>
#include <gtest/gtest.h>
#include "core/geometry/size.h"
#include "media/base/color_plane_layout.h"
#include "media/base/video_frame_layout.h"
#include "media/base/video_types.h"

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
   }
}
