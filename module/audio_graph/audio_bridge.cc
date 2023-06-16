//
// Created by wangrl2016 on 2023/6/9.
//

#include "module/audio_graph/audio_bridge.h"

namespace audio_graph {
    bool AudioBridge::Create() {
        return AudioContext::Instance()->Create();
    }

    bool AudioBridge::Start() {
        return AudioContext::Instance()->Start();
    }

    bool AudioBridge::Stop() {
        return AudioContext::Instance()->Stop();
    }

    bool AudioBridge::Destroy() {
        return AudioContext::Instance()->Destroy();
    }

    bool AudioBridge::Exist() {
        return AudioContext::Instance()->Exist();
    }

    bool AudioBridge::Seek() {
        return AudioContext::Instance()->Seek();
    }

    void AudioBridge::StartBeat() {
        AudioContext::Instance()->StartBeat();
    }

    void AudioBridge::StopBeat() {
        AudioContext::Instance()->StopBeat();
    }

    bool AudioBridge::Clear() {

    }

    std::vector<std::string> AudioBridge::DeviceTypes(int* default_index) {
        return AudioContext::Instance()->DeviceTypes(default_index);
    }

    std::vector<std::string> AudioBridge::InputDeviceNames(int* default_index) {
        return AudioContext::Instance()->InputDeviceNames(default_index);
    }

    std::vector<std::string> AudioBridge::OutputDeviceNames(int* default_index) {
        return AudioContext::Instance()->OutputDeviceNames(default_index);
    }

    std::vector<int> AudioBridge::SampleRates(int* default_index) {
        return AudioContext::Instance()->SampleRates(default_index);
    }

    std::vector<int> AudioBridge::BufferSizes(int* default_index) {
        return AudioContext::Instance()->BufferSizes(default_index);
    }

    bool AudioBridge::UpdateDeviceType(int device_type_index) {
        return AudioContext::Instance()->UpdateDeviceType(device_type_index);
    }

    bool AudioBridge::UpdateInputDevice(int input_device_index) {
        return AudioContext::Instance()->UpdateInputDevice(input_device_index);
    }

    bool AudioBridge::UpdateOutputDevice(int output_device_index) {
        return AudioContext::Instance()->UpdateOutputDevice(output_device_index);
    }

    bool AudioBridge::UpdateSampleRate(int sample_rate_index) {
        return AudioContext::Instance()->UpdateSampleRate(sample_rate_index);
    }

    bool AudioBridge::UpdateBufferSize(int buffer_size_index) {
        return AudioContext::Instance()->UpdateBufferSize(buffer_size_index);
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
