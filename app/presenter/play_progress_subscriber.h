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
    };
}

#endif //CHARACTER_PLAY_PROGRESS_SUBSCRIBER_H
