//
// Created by wangrl2016 on 2023/6/13.
//

#include <glog/logging.h>
#include <QVBoxLayout>
#include "ui/view/widget/song_view.h"
#include "ui/plugin/midi_import.h"

namespace ui {
    SongView::SongView(Song* song) :
            TrackContainerView(song),
            song_(song) {
        LOG(INFO) << __FUNCTION__;
        MidiImport midi(":midi/little_star");
        midi.TryImport(Model());
    }
}