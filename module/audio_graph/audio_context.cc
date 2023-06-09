//
// Created by wangrl2016 on 2023/6/9.
//

#include <memory>
#include "module/audio_graph/audio_context.h"

namespace audio_graph {
    using AudioGraphIOProcessor = juce::AudioProcessorGraph::AudioGraphIOProcessor;
    using Node = juce::AudioProcessorGraph::Node;

    AudioContext& AudioContext::Instance() {
        static AudioContext instance; // instantiated on first use
        return instance;
    }

    bool AudioContext::Create() {
        audio_device_manager_ = std::make_unique<juce::AudioDeviceManager>();
        audio_processor_graph_ = std::make_unique<juce::AudioProcessorGraph>();
        audio_processor_player_ = std::make_unique<juce::AudioProcessorPlayer>();

        return InitAudioDeviceManager(0, 2);
    }

    bool AudioContext::Start() {
        return true;
    }

    bool AudioContext::Stop() {
        return true;
    }

    bool AudioContext::Destroy() {
        return true;
    }

    bool AudioContext::Exist() {
        return true;
    }

    bool AudioContext::Seek() {
        return true;
    }

    void AudioContext::StartBeat() {

    }

    void AudioContext::StopBeat() {

    }

    void AudioContext::Clear() {

    }

    std::string AudioContext::GetCurrentDefaultAudioDeviceName(bool is_input) {
        auto* device_type = audio_device_manager_->getCurrentDeviceTypeObject();

        if (device_type != nullptr) {
            auto device_names = device_type->getDeviceNames();
            return device_names[device_type->getDefaultDeviceIndex(is_input)].toStdString();
        }

        return {};
    }

    bool AudioContext::InitAudioDeviceManager(int num_input_channels, int num_output_channels) {
        juce::String ret;
        if (!audio_device_manager_)
            return false;

        auto* current_device = audio_device_manager_->getCurrentAudioDevice();

        if (num_input_channels < 0)
            num_input_channels = (current_device != nullptr ?
                                  current_device->getActiveInputChannels().countNumberOfSetBits() : 1);

        if (num_output_channels < 0)
            num_output_channels = (current_device != nullptr ?
                                   current_device->getActiveOutputChannels().countNumberOfSetBits() : 2);

        if (num_input_channels > 0 && !juce::RuntimePermissions::isGranted(
                juce::RuntimePermissions::recordAudio)) {
            juce::RuntimePermissions::request(juce::RuntimePermissions::recordAudio,
                                              [num_input_channels, num_output_channels, this](bool granted) {
                                                  if (granted) {
                                                      InitAudioDeviceManager(num_input_channels, num_output_channels);
                                                  }
                                              });

            num_input_channels = 0;
        }

        if (audio_device_manager_->getCurrentAudioDevice() != nullptr) {
            auto setup = audio_device_manager_->getAudioDeviceSetup();

            auto num_inputs = std::max(num_input_channels, setup.inputChannels.countNumberOfSetBits());
            auto num_outputs = std::max(num_output_channels, setup.outputChannels.countNumberOfSetBits());

            auto old_inputs = setup.inputChannels.countNumberOfSetBits();
            auto old_outputs = setup.outputChannels.countNumberOfSetBits();

            if (old_inputs != num_inputs || old_outputs != num_outputs) {
                if (old_inputs == 0 && old_outputs == 0) {
                    ret = audio_device_manager_->initialise(num_input_channels,
                                                            num_output_channels,
                                                            nullptr,
                                                            true,
                                                            {},
                                                            nullptr);
                } else {
                    setup.useDefaultInputChannels = setup.useDefaultOutputChannels = false;

                    setup.inputChannels.clear();
                    setup.outputChannels.clear();

                    setup.inputChannels.setRange(0, num_inputs, true);
                    setup.outputChannels.setRange(0, num_outputs, true);

                    if (old_inputs == 0 && num_inputs > 0 && setup.inputDeviceName.isEmpty()) {
                        setup.inputDeviceName = GetCurrentDefaultAudioDeviceName(true);
                    }

                    if (old_outputs == 0 && num_outputs > 0 && setup.outputDeviceName.isEmpty()) {
                        setup.outputDeviceName = GetCurrentDefaultAudioDeviceName(false);
                    }

                    ret = audio_device_manager_->setAudioDeviceSetup(setup, false);
                }
            }
        } else {
            ret = audio_device_manager_->initialise(num_input_channels,
                                                    num_output_channels,
                                                    nullptr,
                                                    true,
                                                    {},
                                                    nullptr);
        }

        if (ret.isEmpty()) {
            return true;
        } else {
            return false;
        }
    }

    bool AudioContext::InitAudioGraph() {
        audio_processor_graph_->clear();

        audio_processor_graph_->addNode(
                std::make_unique<AudioGraphIOProcessor>(AudioGraphIOProcessor::audioOutputNode));
    }
}
