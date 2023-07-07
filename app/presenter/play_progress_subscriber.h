//
// Created by wangrl2016 on 2023/6/23.
//

#ifndef CHARACTER_PLAY_PROGRESS_SUBSCRIBER_H
#define CHARACTER_PLAY_PROGRESS_SUBSCRIBER_H

#include <QObject>

namespace app {
    class PlayProgressSubscriber {
    public:
        virtual void NotifyPlayProgress(double sec) = 0;

        virtual void NotifyLoop(bool loop) = 0;

        virtual void NotifyLoopStart(double loop_start) = 0;

        virtual void NotifyLoopEnd(double loop_end) = 0;
    };
}

#endif //CHARACTER_PLAY_PROGRESS_SUBSCRIBER_H
