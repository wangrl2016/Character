//
// Created by wangrl2016 on 2023/6/9.
//

#include <memory>
#include <glog/logging.h>
#include "module/audio_graph/audio_context.h"
#include "module/audio_graph/constant.h"
#include "module/audio_graph/gain_node.h"
#include "module/audio_graph/oscillator_node.h"
#include "mixer.h"
#include "piano_node.h"

namespace audio_graph {
    AudioContext* AudioContext::Instance() {
        // Using pointer for AudioProcessorGraph release.
        // Instantiated on first use.
        static auto* instance = new AudioContext;
        return instance;
    }

    void AudioContext::DeleteInstance() {
        delete Instance();
    }

    bool AudioContext::Create() {
        // LOG(INFO) << __FUNCTION__;
        juce::MessageManager::getInstance();

        audio_device_manager_ = std::make_unique<juce::AudioDeviceManager>();
        audio_processor_graph_ = std::make_unique<juce::AudioProcessorGraph>();
        audio_processor_player_ = std::make_unique<juce::AudioProcessorPlayer>();

        return InitAudioDeviceManager(kDefaultInputChannelCount,
                                      kDefaultOutputChannelCount);
    }

    bool AudioContext::Start() {
        // LOG(INFO) << __FUNCTION__;
        audio_device_manager_->addChangeListener(this);
        audio_device_manager_->addAudioCallback(audio_processor_player_.get());
        audio_processor_player_->setProcessor(audio_processor_graph_.get());

        return InitAudioGraph();
    }

    bool AudioContext::Stop() {
        // LOG(INFO) << __FUNCTION__;
        audio_device_manager_->removeChangeListener(this);
        audio_device_manager_->removeAudioCallback(audio_processor_player_.get());
        audio_processor_player_->setProcessor(nullptr);
        return true;
    }

    bool AudioContext::Destroy() {
        // LOG(INFO) << __FUNCTION__;

        audio_device_manager_.reset();
        audio_processor_player_.reset();
        audio_processor_graph_.reset();

        juce::MessageManager::getInstance()->stopDispatchLoop();
        juce::DeletedAtShutdown::deleteAll();
        juce::MessageManager::deleteInstance();

        DeleteInstance();
        return true;
    }

    bool AudioContext::Exist() {
        return true;
    }

    bool AudioContext::Seek() {
        return true;
    }

    void AudioContext::StartBeat() {
        // LOG(INFO) << __FUNCTION__;
        auto* oscillator_node = audio_processor_graph_->getNodeForId(
                oscillator_node_->nodeID);
        if (oscillator_node) {
            dynamic_cast<OscillatorNode*>(oscillator_node->getProcessor())->StartBeat();
        }
        auto* gain_node = audio_processor_graph_->getNodeForId(
                gain_node_->nodeID);
        if (gain_node) {
            dynamic_cast<GainNode*>(gain_node->getProcessor())->StartBeat();
        }
    }

    void AudioContext::StopBeat() {
        // LOG(INFO) << __FUNCTION__;
        auto* oscillator_node = audio_processor_graph_->getNodeForId(
                oscillator_node_->nodeID);
        if (oscillator_node) {
            dynamic_cast<OscillatorNode*>(oscillator_node->getProcessor())->StopBeat();
        }
        auto* gain_node = audio_processor_graph_->getNodeForId(
                gain_node_->nodeID);
        if (gain_node) {
            dynamic_cast<GainNode*>(gain_node->getProcessor())->StopBeat();
        }
    }

    void AudioContext::Clear() {

    }

    std::vector<std::string> AudioContext::DeviceTypes(int* default_index) {
        const juce::OwnedArray<juce::AudioIODeviceType>& types =
                audio_device_manager_->getAvailableDeviceTypes();

        std::vector<std::string> ret = {};
        for (auto& type: types) {
            ret.push_back(type->getTypeName().toStdString());
        }
        *default_index = ret.empty() ? kInvalidIndex : current_device_type_;

        return ret;
    }

    std::vector<std::string> AudioContext::InputDeviceNames(int* default_index) {
        std::vector<std::string> ret = {};
        auto type = audio_device_manager_->getCurrentDeviceTypeObject();
        if (type) {
            juce::StringArray input_device_names(type->getDeviceNames(true));
            for (auto& name: input_device_names) {
                ret.push_back(name.toStdString());
            }
            *default_index = type->getDefaultDeviceIndex(true);
        }
        return ret;
    }

    std::vector<std::string> AudioContext::OutputDeviceNames(int* default_index) {
        std::vector<std::string> ret = {};
        auto type = audio_device_manager_->getCurrentDeviceTypeObject();
        if (type) {
            juce::StringArray output_device_names(type->getDeviceNames(false));
            for (auto& name: output_device_names) {
                ret.push_back(name.toStdString());
            }
            *default_index = type->getDefaultDeviceIndex(false);
        }
        return ret;
    }

    std::vector<int> AudioContext::SampleRates(int* default_index) {
        std::vector<int> ret = {};
        auto device = audio_device_manager_->getCurrentAudioDevice();
        int current_sample_rate = juce::roundToInt(device->getCurrentSampleRate());
        auto rates = device->getAvailableSampleRates();
        for (int i = 0; i < rates.size(); i++) {
            ret.push_back(juce::roundToInt(rates[i]));
            if (juce::roundToInt(rates[i]) == current_sample_rate)
                *default_index = i;
        }

        return ret;
    }

    std::vector<int> AudioContext::BufferSizes(int* default_index) {
        std::vector<int> ret = {};
        auto device = audio_device_manager_->getCurrentAudioDevice();
        int current_buffer_size = juce::roundToInt(device->getCurrentBufferSizeSamples());
        auto buffer_sizes = device->getAvailableBufferSizes();
        for (int i = 0; i < buffer_sizes.size(); i++) {
            ret.push_back(juce::roundToInt(buffer_sizes[i]));
            if (juce::roundToInt(buffer_sizes[i]) == current_buffer_size)
                *default_index = i;
        }

        return ret;
    }

    bool AudioContext::UpdateDeviceType(int device_type_index) {
        LOG(INFO) << __FUNCTION__ << ", index " << device_type_index;
        return true;
    }

    bool AudioContext::UpdateInputDevice(int input_device_index) {
        LOG(INFO) << __FUNCTION__ << ", index " << input_device_index;
        return true;
    }

    bool AudioContext::UpdateOutputDevice(int output_device_index) {
        LOG(INFO) << __FUNCTION__ << ", index " << output_device_index;
        return true;
    }

    bool AudioContext::UpdateSampleRate(int sample_rate_index) {
        LOG(INFO) << __FUNCTION__ << ", index " << sample_rate_index;
        return true;
    }

    bool AudioContext::UpdateBufferSize(int buffer_size_index) {
        LOG(INFO) << __FUNCTION__ << ", index " << buffer_size_index;
        return true;
    }

    void AudioContext::TapDown(int pitch) {
        LOG(INFO) << __FUNCTION__ << ", pitch " << pitch;
        auto* node = audio_processor_graph_->getNodeForId(piano_node_->nodeID);
        if(node) {
            dynamic_cast<PianoNode*>(node->getProcessor())->TapDown(pitch);
        }
    }

    void AudioContext::TapUp(int pitch) {
        LOG(INFO) << __FUNCTION__ << ", pitch " << pitch;
        auto* node = audio_processor_graph_->getNodeForId(piano_node_->nodeID);
        if(node) {
            dynamic_cast<PianoNode*>(node->getProcessor())->TapUp(pitch);
        }
    }

    juce::String AudioContext::GetCurrentDefaultAudioDeviceName(bool is_input) {
        auto* device_type = audio_device_manager_->getCurrentDeviceTypeObject();

        if (device_type != nullptr) {
            auto device_names = device_type->getDeviceNames();
            return device_names[device_type->getDefaultDeviceIndex(is_input)];
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
            juce::RuntimePermissions::request(
                    juce::RuntimePermissions::recordAudio,
                    [num_input_channels, num_output_channels, this](bool granted) {
                        if (granted) {
                            InitAudioDeviceManager(num_input_channels, num_output_channels);
                        }
                    });

            num_input_channels = 0;
        }

        if (audio_device_manager_->getCurrentAudioDevice() != nullptr) {
            auto setup = audio_device_manager_->getAudioDeviceSetup();

            auto num_inputs = std::max(num_input_channels,
                                       setup.inputChannels.countNumberOfSetBits());
            auto num_outputs = std::max(num_output_channels,
                                        setup.outputChannels.countNumberOfSetBits());

            auto old_inputs = setup.inputChannels.countNumberOfSetBits();
            auto old_outputs = setup.outputChannels.countNumberOfSetBits();

            if (old_inputs != num_inputs || old_outputs != num_outputs) {
                if (old_inputs == 0 && old_outputs == 0) {
                    ret = audio_device_manager_->initialise(
                            num_input_channels,
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
            ret = audio_device_manager_->initialise(
                    num_input_channels,
                    num_output_channels,
                    nullptr,
                    true,
                    {},
                    nullptr);
        }

        DumpDeviceInfo();

        return ret.isEmpty();
    }

    static juce::String GetListOfActiveBits(const juce::BigInteger& b) {
        juce::StringArray bits;
        for (auto i = 0; i <= b.getHighestBit(); i++) {
            if (b[i]) {
                bits.add(juce::String(i));
            }
        }
        return bits.joinIntoString(", ");
    }

    void AudioContext::DumpDeviceInfo() {
        LOG(INFO) << __FUNCTION__;
        LOG(INFO) << "Current audio device type: " <<
                  ((audio_device_manager_->getCurrentDeviceTypeObject() != nullptr) ?
                   audio_device_manager_->getCurrentDeviceTypeObject()->getTypeName() : "<none>");

        if (auto* device = audio_device_manager_->getCurrentAudioDevice()) {
            LOG(INFO) << "Current audio device: " << device->getName().quoted();
            LOG(INFO) << "Sample rate:  " << device->getCurrentSampleRate() << " Hz";
            LOG(INFO) << "Block size: " << device->getCurrentBufferSizeSamples() << " samples";
            LOG(INFO) << "Input latency: " << device->getInputLatencyInSamples() << " samples";
            LOG(INFO) << "Output latency: " << device->getOutputLatencyInSamples() << " samples";
            LOG(INFO) << "Bit depth: " << device->getCurrentBitDepth();
            LOG(INFO) << "Input channel names: " << device->getInputChannelNames()
                    .joinIntoString(", ").toStdString();
            LOG(INFO) << "Active input channels: " <<
                      GetListOfActiveBits(device->getActiveInputChannels()).toStdString();
            LOG(INFO) << "Output channel names: " <<
                      device->getOutputChannelNames().joinIntoString(", ").toStdString();
            LOG(INFO) << "Active output channels: " <<
                      GetListOfActiveBits(device->getActiveOutputChannels());
        }
    }

    bool AudioContext::InitAudioGraph() {
        audio_processor_graph_->enableAllBuses();
        audio_processor_graph_->clear();

        audio_input_node_ = audio_processor_graph_->addNode(
                std::make_unique<AudioGraphIOProcessor>(
                        AudioGraphIOProcessor::audioInputNode));
        audio_output_node_ = audio_processor_graph_->addNode(
                std::make_unique<AudioGraphIOProcessor>(
                        AudioGraphIOProcessor::audioOutputNode));

        midi_input_node_ = audio_processor_graph_->addNode(
                std::make_unique<AudioGraphIOProcessor>(
                        AudioGraphIOProcessor::midiInputNode));
        midi_output_node_ = audio_processor_graph_->addNode(
                std::make_unique<AudioGraphIOProcessor>(
                        AudioGraphIOProcessor::midiOutputNode));

        if (!audio_input_node_ || !audio_output_node_
            || !midi_input_node_ || !midi_output_node_) {
            return false;
        }

        ConnectAudioNodes();

        ConnectMidiNodes();

        return true;
    }

    void AudioContext::ConnectAudioNodes() {
        int channel_count = audio_device_manager_->getCurrentAudioDevice()
                ->getActiveOutputChannels().toInteger();

        gain_node_ = audio_processor_graph_->addNode(std::make_unique<GainNode>());
        master_mixer_node_ = audio_processor_graph_->addNode(std::make_unique<Mixer>());
        oscillator_node_ = audio_processor_graph_->addNode(std::make_unique<OscillatorNode>());
        piano_node_ = audio_processor_graph_->addNode(std::make_unique<PianoNode>());

        for (int channel = 0; channel < channel_count; channel++) {
            audio_processor_graph_->addConnection(
                    {{oscillator_node_->nodeID, channel},
                     {master_mixer_node_->nodeID,       kDefaultOutputChannelCount +channel}});

            audio_processor_graph_->addConnection(
                    {{piano_node_->nodeID, channel},
                     {master_mixer_node_->nodeID,  channel}});

            audio_processor_graph_->addConnection(
                    {{master_mixer_node_->nodeID, channel},
                     {gain_node_->nodeID, channel}});

            audio_processor_graph_->addConnection(
                    {{gain_node_->nodeID,         channel},
                     {audio_output_node_->nodeID, channel}});

            // audio_processor_graph_->addConnection(
            //         {{audio_input_node_->nodeID,  channel},
            //          {audio_output_node_->nodeID, channel}});
        }
    }

    void AudioContext::ConnectMidiNodes() {
        audio_processor_graph_->addConnection(
                {{midi_input_node_->nodeID,  juce::AudioProcessorGraph::midiChannelIndex},
                 {midi_output_node_->nodeID, juce::AudioProcessorGraph::midiChannelIndex}});
    }

}
