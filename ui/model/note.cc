//
// Created by wangrl2016 on 2023/6/10.
//

#include <QtGlobal>
#include <utility>
#include "ui/model/note.h"

namespace ui {
    Note::Note(int pos, int length,
               int key, float volume,
               float panning, QString pronouncing,
               QString lyric) :
            key_(qBound(0, key, kNumKeys)),
            volume_(volume),
            panning_(panning),
            pos_(pos),
            length_(length),
            pronouncing_(std::move(pronouncing)),
            lyric_(std::move(lyric)),
            selected_(false),
            old_key_(qBound(0, key, kNumKeys)),
            old_pos_(pos),
            old_length_(length),
            is_playing_(false) {

    }

    Note::Note(const Note& note) :
            key_(note.key_),
            volume_(note.volume_),
            panning_(note.panning_),
            pos_(note.pos_),
            length_(note.length_),
            pronouncing_(note.pronouncing_),
            lyric_(note.lyric_),
            selected_(note.selected_),
            old_key_(note.old_key_),
            old_pos_(note.old_pos_),
            old_length_(note.old_length_),
            is_playing_(note.is_playing_) {

    }

    Note::~Note() = default;
}