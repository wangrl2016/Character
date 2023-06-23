//
// Created by wangrl2016 on 2023/6/23.
//

#ifndef CHARACTER_PLAY_PROGRESS_MODEL_H
#define CHARACTER_PLAY_PROGRESS_MODEL_H

namespace app {
    class PlayProgressModel {
    public:
        explicit PlayProgressModel(double sec) : play_progress_(sec) {}

        [[nodiscard]] double play_progress() const { return play_progress_; }

        void set_play_progress(double play_progress) {
            play_progress_ = play_progress;
        }

    private:
        double play_progress_;
    };
}

#endif //CHARACTER_PLAY_PROGRESS_MODEL_H
