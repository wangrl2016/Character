//
// Created by wangrl2016 on 2023/6/10.
//

#include <QtGlobal>
#include <utility>
#include "app/model/music/note.h"

namespace app {
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

    Note::~Note() = default;
}