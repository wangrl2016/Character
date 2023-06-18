//
// Created by wangrl2016 on 2023/6/18.
//

#ifndef CHARACTER_MIDI_IMPORT_H
#define CHARACTER_MIDI_IMPORT_H

#include "ui/plugin/import_filter.h"

namespace ui {
    class MidiImport : public ImportFilter {
    public:
        MidiImport(const QString& file);

        ~MidiImport() override = default;

    private:
        bool TryImport(TrackContainer* tc) override;
    };
}

#endif //CHARACTER_MIDI_IMPORT_H
