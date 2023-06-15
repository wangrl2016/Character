//
// Created by wangrl2016 on 2023/6/9.
//

#ifndef CHARACTER_AUDIO_CONTEXT_H
#define CHARACTER_AUDIO_CONTEXT_H

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_core/juce_core.h>

namespace audio_graph {
    using AudioGraphIOProcessor = juce::AudioProcessorGraph::AudioGraphIOProcessor;
    using Node = juce::AudioProcessorGraph::Node;

    class AudioContext : public juce::ChangeListener {
    public:
        void changeListenerCallback(juce::ChangeBroadcaster* override) {
            DumpDeviceInfo();
        }

        static AudioContext* Instance();

        void DeleteInstance();

        bool Create();

        bool Start();

        bool Stop();

        bool Destroy();

        bool Exist();

        bool Seek();

        void StartBeat();

        void StopBeat();

        void Clear();

        std::vector<std::string> DeviceTypes(int* default_index = nullptr);

        std::vector<std::string>& InputDeviceNames(int* default_index = nullptr);

        std::vector<std::string>& OutputDeviceNames(int* default_index = nullptr);

        std::vector<int>& SampleRates(int* default_index = nullptr);

        std::vector<int>& BufferSizes(int* default_index = nullptr);

        bool UpdateDeviceType(int device_type_index);

        bool UpdateInputDevice(int input_device_index);

        bool UpdateOutputDevice(int output_device_index);

        bool UpdateSampleRate(int sample_rate_index);

        bool UpdateBufferSize(int buffer_size_index);

    private:
        AudioContext() = default;

        ~AudioContext() = default;

        juce::String GetCurrentDefaultAudioDeviceName(bool is_input);

        // JUCE/examples/DemoRunner/Source/Demos/JUCEDemos.cpp
        bool InitAudioDeviceManager(int num_input_channels,
                                    int num_output_channels);

        void DumpDeviceInfo();

        bool InitAudioGraph();

        void ConnectAudioNodes();

        void ConnectMidiNodes();

        // https://docs.juce.com/master/tutorial_audio_processor_graph.html
        std::unique_ptr<juce::AudioDeviceManager> audio_device_manager_;
        std::unique_ptr<juce::AudioProcessorGraph> audio_processor_graph_;
        std::unique_ptr<juce::AudioProcessorPlayer> audio_processor_player_;

        Node::Ptr audio_input_node_;
        Node::Ptr audio_output_node_;
        Node::Ptr midi_input_node_;
        Node::Ptr midi_output_node_;

        Node::Ptr gain_node_;
        Node::Ptr oscillator_node_;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioContext)
    };
}

#endif //CHARACTER_AUDIO_CONTEXT_H
