//
// Created by wangrl2016 on 2023/6/18.
//

#include <glog/logging.h>
#include "ui/plugin/midi_import.h"
#include "third_party/portsmf/include/allegro.h"

namespace ui {
    #define MakeID(a, b, c, d) (0 | (a | (b << 8) | (c << 16) | (d << 24)))

    Plugin::Descriptor midi_import_plugin_descriptor = {
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            0x0100,
            Plugin::kImportFilter,
            nullptr
    };

    MidiImport::MidiImport(const QString& file) :
            ImportFilter(file, &midi_import_plugin_descriptor) {

    }

    bool MidiImport::TryImport(TrackContainer* tc) {
        switch (ReadID()) {
            case MakeID('M', 'T', 'h', 'd'):
                LOG(INFO) << __FUNCTION__ << ": found MThd";
                return ReadSMF(tc);
            case MakeID('R', 'I', 'F', 'F'):
                LOG(INFO) << __FUNCTION__ << ": found RIFF";
                return ReadRIFF(tc);
            default:
                LOG(INFO) << __FUNCTION__ << ": not a standard MIDI file";
                return false;
        }
    }

    bool MidiImport::ReadSMF(TrackContainer* tc) {
        std::istringstream stream(ReadAllData().toStdString());
        auto seq = new Alg_seq(stream, true);
        seq->convert_to_beats();

        // Tracks
        for (int t = 0; t < seq->tracks(); t++) {
            QString track_name = QString(tr("Track") + " %1").arg(t);
            Alg_track_ptr track = seq->track(t);

        }
    }

    bool MidiImport::ReadRIFF(TrackContainer* tc) {

    }
}
