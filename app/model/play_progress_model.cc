//
// Created by wangrl2016 on 2023/6/26.
//

#include "app/model/play_progress_model.h"

namespace app {
    void PlayProgressModel::set_loop_start(double loop_start) {
        if (loop_end_ - loop_start < kMinLoopDuration)
            loop_start_ = loop_end_ - kMinLoopDuration;
        else
            loop_start_ = loop_start;
    }

    void PlayProgressModel::set_loop_end(double loop_end) {
        if (loop_start_ + loop_end < kMinLoopDuration)
            loop_end_ = loop_start_ + kMinLoopDuration;
        else
            loop_end_ = loop_end;
    }

    void PlayProgressModel::SetLoopRange(double loop_start, double loop_end) {
        if (loop_end - loop_start < kMinLoopDuration)
            return;
        else {
            loop_start_ = loop_start;
            loop_end_ = loop_end;
        }
    }
}
