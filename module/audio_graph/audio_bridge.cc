//
// Created by wangrl2016 on 2023/6/9.
//

#include "module/audio_graph/audio_bridge.h"

namespace audio_graph {
    bool AudioBridge::Create() {
        return AudioContext::Instance().Create();
    }

    bool AudioBridge::Start() {
        return AudioContext::Instance().Start();
    }

    bool AudioBridge::Stop() {
        return AudioContext::Instance().Stop();
    }

    bool AudioBridge::Destroy() {
        return AudioContext::Instance().Destroy();
    }

    bool AudioBridge::Exist() {
        return AudioContext::Instance().Exist();
    }

    bool AudioBridge::Seek() {
        return AudioContext::Instance().Seek();
    }

    void AudioBridge::StartBeat() {

    }

    void AudioBridge::StopBeat() {

    }

    bool AudioBridge::Clear() {

    }

    TrackID AudioBridge::AddTrack(Track::TrackType type) {

    }

    bool AudioBridge::RemoveTrack(TrackID id) {

    }

    void AudioBridge::ClearTrack(TrackID id) {

    }

    void AudioBridge::SetTrackVolume(TrackID id, float volume) {

    }
}
