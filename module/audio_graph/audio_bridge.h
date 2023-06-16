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

        static std::vector<std::string> DeviceTypes(int* default_index = nullptr);

        static std::vector<std::string> InputDeviceNames(int* default_index = nullptr);

        static std::vector<std::string> OutputDeviceNames(int* default_index = nullptr);

        static std::vector<int> SampleRates(int* default_index = nullptr);

        static std::vector<int> BufferSizes(int* default_index = nullptr);

        static bool UpdateDeviceType(int device_type_index);

        static bool UpdateInputDevice(int input_device_index);

        static bool UpdateOutputDevice(int output_device_index);

        static bool UpdateSampleRate(int sample_rate_index);

        static bool UpdateBufferSize(int buffer_size_index);


        TrackID AddTrack(Track::TrackType type);

        bool RemoveTrack(TrackID id);

        void ClearTrack(TrackID id);

        void SetTrackVolume(TrackID id, float volume);
    };
}

#endif //CHARACTER_AUDIO_BRIDGE_H
