//
// Created by wangrl2016 on 2023/6/9.
//

#ifndef CHARACTER_AUDIO_BRIDGE_H
#define CHARACTER_AUDIO_BRIDGE_H

#include <future>
#include <vector>
#include "module/audio_graph/track.h"

namespace audio_graph {
    using PlayProgressHandler = std::function<void(double sec)>;

    class AudioBridge {
    public:
        // create / destroy
        static bool Create();

        // start / stop
        static bool Start();

        static bool Stop();

        static bool Destroy();

        static bool Exist();

        static void Seek(double sec);

        static void StartBeat();

        static void StopBeat();

        static bool Clear();

        // @return track id
        static int AddTrack(Track::TrackType type);

        static bool RemoveTrack(int track_id);

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

        static void TapDown(int pitch);

        static void TapUp(int pitch);

        static void RegisterPlayProgressHandler(PlayProgressHandler handler);

        static void OnPlayProgressCallback(double sec);

    private:
        static PlayProgressHandler play_progress_handler;
    };
}

#endif //CHARACTER_AUDIO_BRIDGE_H
