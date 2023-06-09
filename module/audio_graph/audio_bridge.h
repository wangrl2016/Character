//
// Created by wangrl2016 on 2023/6/9.
//

#ifndef CHARACTER_AUDIO_BRIDGE_H
#define CHARACTER_AUDIO_BRIDGE_H

#include "module/audio_graph/audio_context.h"
#include "module/audio_graph/track.h"

namespace audio_graph {
    class AudioBridge {
    public:
        // create / destroy
        static bool Create();

        // start / stop
        static bool Start();

        static bool Stop();

        static bool Destroy();

        static bool Exist();

        static bool Seek();

        static void StartBeat();

        static void StopBeat();

        static bool Clear();

        TrackID AddTrack(Track::TrackType type);

        bool RemoveTrack(TrackID id);

        void ClearTrack(TrackID id);

        void SetTrackVolume(TrackID id, float volume);
    };
}

#endif //CHARACTER_AUDIO_BRIDGE_H
