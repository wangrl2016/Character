//
// Created by wangrl2016 on 2023/6/12.
//

#ifndef CHARACTER_CLIP_H
#define CHARACTER_CLIP_H

#include <QColor>
#include "ui/model/model.h"

namespace ui {
    class Track;

    class Clip : public Model {
    public:
    private:
        enum Action {
            kNoAction,
            kMove,
            kResize,
        };

        std::shared_ptr<Track> track_;

        QString name_;

        int start_pos_;
        int length_;

        bool mute_;
        bool solo_;

        QColor color_;

    };
}

#endif //CHARACTER_CLIP_H
