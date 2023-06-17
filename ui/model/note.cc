//
// Created by wangrl2016 on 2023/6/10.
//

#include <QtGlobal>
#include "ui/model/note.h"

namespace ui {
    Note::Note(int pos, int length, int key, float volume, float panning) :
            selected_(false),
            old_key_(qBound(0, key, kNumKeys)),
            old_pos_(pos),
            old_length_(length),
            is_playing_(false),
            key_(qBound(0, key, kNumKeys)),
            volume_(volume),
            panning_(panning),
            length_(length),
            pos_(pos) {}

    Note::Note(const Note& note) :
            selected_(note.selected_),
            old_key_(note.old_key_),
            old_pos_(note.old_pos_),
            old_length_(note.old_length_),
            is_playing_(note.is_playing_),
            key_(note.key_),
            volume_(note.volume_),
            panning_(note.panning_),
            length_(note.length_),
            pos_(note.pos_) {}

    Note::~Note() = default;
}