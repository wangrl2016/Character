//
// Created by wangrl2016 on 2023/6/23.
//

#ifndef CHARACTER_PLAY_PROGRESS_MODEL_H
#define CHARACTER_PLAY_PROGRESS_MODEL_H

namespace app {
    constexpr double kDefaultLoopDuration = 2.0;
    constexpr double kMinLoopDuration = kDefaultLoopDuration;

    class PlayProgressModel {
    public:
        explicit PlayProgressModel() :
                play_progress_(0.0),
                loop_start_(0.0),
                loop_end_(loop_start_ + kDefaultLoopDuration) {}

        [[nodiscard]] double play_progress() const { return play_progress_; }

        void set_play_progress(double play_progress) {
            play_progress_ = play_progress;
        }

        [[nodiscard]] double loop_start() const { return loop_start_; }

        void set_loop_start(double loop_start) {
            loop_start_ = loop_start;
        }

        [[nodiscard]] double loop_end() const { return loop_end_; }

        void set_loop_end(double loop_end) {
            loop_end_ = loop_end;
        }

    private:
        double play_progress_;
        double loop_start_;
        double loop_end_;
    };
}

#endif //CHARACTER_PLAY_PROGRESS_MODEL_H
