//
// Created by wangrl2016 on 2023/6/12.
//

#include "ui/model/track.h"
#include "ui/model/clip.h"

namespace ui {
    Clip::Clip(Track* t) : Model(t),
        track_(t),
        start_pos_(0),
        length_(0),
        mute_(false),
        solo_(false),
        color_(128, 128, 128) {
        if (track()) {
            track()->AddClip(this);
        }
        //MovePosition(0);
        //ChangeLength(0);
    }

    Clip::~Clip() {
        emit DestroyClip();

        if (track()) {
            track()->RemoveClip(this);
        }
    }

    void Clip::MovePosition(int pos) {
        if (start_pos_ != pos) {
            start_pos_ = pos;

            emit PositionChanged();
        }
    }

    void Clip::ChangeLength(int length) {
        length_ = length;
        emit LengthChanged();
    }

    bool Clip::ComparePosition(const Clip* a, const Clip* b) {
        return a->start_pos() < b->start_pos();
    }

    void Clip::CopyStateTo(Clip* src, Clip* dst) {

    }

    void Clip::ToggleMute() {
        mute_ = !mute_;
        emit DataChanged();
    }

}
