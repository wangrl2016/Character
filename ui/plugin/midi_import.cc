//
// Created by wangrl2016 on 2023/6/18.
//

#include <glog/logging.h>

#include <utility>
#include "ui/plugin/midi_import.h"
#include "third_party/portsmf/include/allegro.h"
#include "ui/model/instrument_track.h"
#include "ui/model/midi_clip.h"

namespace ui {
#define MakeID(a, b, c, d) (0 | ((a) | ((b) << 8) | ((c) << 16) | ((d) << 24)))

    class MidiChannel {
    public:
        MidiChannel() : instrument_track(nullptr),
                        clip(nullptr),
                        instrument(nullptr),
                        is_sf(false),
                        has_note(false) {}

        InstrumentTrack* instrument_track;
        MidiClip* clip;
        Instrument* instrument;
        bool is_sf;
        bool has_note;
        QString track_name;

        MidiChannel* Create(TrackContainer* tc, QString name) {
            if (!instrument_track) {
                instrument_track = dynamic_cast<InstrumentTrack*>(
                        Track::Create(Track::kInstrumentTrack, tc));
                track_name = std::move(name);

                // create a default clip
                clip = dynamic_cast<MidiClip*>(instrument_track->CreateClip(0));
            }

            return this;
        }


    };

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
        if (!OpenFile()) {
            return false;
        }

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

        // tracks
        int count = 0;
        for (int t = 0; t < seq->tracks(); t++) {
            QString track_name = QString(tr("Track") + " %1").arg(t);
            Alg_track_ptr track = seq->track(t);

            // now look at events
            for (int e = 0; e < track->length(); e++) {
                Alg_event_ptr event = (*track)[e];

                if (event->chan == -1) {

                } else if (event->is_note()) {
                    auto note = dynamic_cast<Alg_note_ptr>(event);
                    LOG(INFO) << "Note: " << note->get_identifier()
                              << ", start_time: " << note->get_start_time()
                              << ", duration " << note->get_duration()
                              << ", loud " << note->get_loud()
                              << ", count " << count++;
                }
            }
            LOG(INFO) << "__end__";
        }

        return true;
    }

    bool MidiImport::ReadRIFF(TrackContainer* tc) {

    }
}
