//
// Created by wangrl2016 on 2023/6/23.
//

#ifndef CHARACTER_PLAY_PROGRESS_VIEW_H
#define CHARACTER_PLAY_PROGRESS_VIEW_H

namespace app {
    class PlayProgressPresenter;

    class PlayProgressView {
    public:
        virtual void Subscribe(PlayProgressPresenter* presenter);

        virtual void PlayProgressUpdate();

    protected:
        PlayProgressPresenter* play_progress_presenter_ = nullptr;
    };
}

#endif //CHARACTER_PLAY_PROGRESS_VIEW_H
