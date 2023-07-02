//
// Created by wangrl2016 on 2023/6/23.
//

#ifndef CHARACTER_PLAY_PROGRESS_PRESENTER_H
#define CHARACTER_PLAY_PROGRESS_PRESENTER_H

#include "app/presenter/play_progress_subscriber.h"
#include "app/model/play_progress_model.h"
#include "play_progress_view.h"

namespace app {
    class PlayProgressPresenter : public PlayProgressSubscriber {
    public:
        explicit PlayProgressPresenter(PlayProgressModel* model);

        virtual ~PlayProgressPresenter();

        void AddView(PlayProgressView* view);

        void NotifyPlayProgress(double sec) override;

        [[nodiscard]] double PlayProgress() const;

        [[nodiscard]] double LoopStart() const;

        [[nodiscard]] double LoopEnd() const;

    private:
        PlayProgressModel* model_;

        QList<PlayProgressView*> view_list_;
    };
}


#endif //CHARACTER_PLAY_PROGRESS_PRESENTER_H
