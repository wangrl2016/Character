//
// Created by wangrl2016 on 2023/6/18.
//

#ifndef CHARACTER_MIDI_IMPORT_H
#define CHARACTER_MIDI_IMPORT_H

#include "app/plugin/import_filter.h"

namespace app {
    class MidiImport : public ImportFilter {
    public:
        MidiImport(const QString& file);

        ~MidiImport() override = default;

        bool TryImport() override;
    private:
        bool ReadSMF();

        bool ReadRIFF();

        inline int Read32LE() {
            int value = ReadByte();
            value |= ReadByte() << 8;
            value |= ReadByte() << 16;
            value |= ReadByte() << 24;
            return value;
        }

        inline int ReadID() {
            return Read32LE();
        }
    };
}

#endif //CHARACTER_MIDI_IMPORT_H
