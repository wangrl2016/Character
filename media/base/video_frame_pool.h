//
// Created by admin on 2023/7/17.
//

#ifndef CHARACTER_VIDEO_FRAME_POOL_H
#define CHARACTER_VIDEO_FRAME_POOL_H

namespace media {
    // Simple VideoFrame poll used to avoid unnecessarily allocating and destroying
    // VideoFrame objects. The pool manages the memory for the VideoFrame
    // returned by CreateFrame().
    class VideoFramePool {
    public:
        VideoFramePool();

        VideoFramePool(const VideoFramePool&) = delete;

        VideoFramePool& operator=(const VideoFramePool&) = delete;

        ~VideoFramePool();
    };
}

#endif //CHARACTER_VIDEO_FRAME_POOL_H
