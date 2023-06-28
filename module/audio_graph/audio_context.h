//
// Created by wangrl2016 on 2023/6/9.
//

#ifndef CHARACTER_AUDIO_CONTEXT_H
#define CHARACTER_AUDIO_CONTEXT_H

#include <juce_core/juce_core.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_utils/juce_audio_utils.h>

namespace audio_graph {
    constexpr int kInvalidIndex = -1;

    using AudioGraphIOProcessor = juce::AudioProcessorGraph::AudioGraphIOProcessor;
    using Node = juce::AudioProcessorGraph::Node;

    class AudioContext : public juce::ChangeListener,
        public juce::MidiInputCallback,
        public juce::MidiKeyboardState::Listener {
    public:
        void changeListenerCallback(juce::ChangeBroadcaster* override) override {
            DumpDeviceInfo();
        }

        void handleIncomingMidiMessage (juce::MidiInput* source,
                                        const juce::MidiMessage& message) override;

        void handleNoteOn(juce::MidiKeyboardState* source,
                          int midi_channel,
                          int midi_note_number,
                          float velocity) override;

        void handleNoteOff(juce::MidiKeyboardState* source,
                           int midi_channel,
                           int midi_note_number,
                           float velocity) override;

        static AudioContext* Instance();

        void DeleteInstance();

        bool Create();

        bool Start();

        bool Stop();

        bool Destroy();

        bool Exist();

        void Seek(double sec);

        void StartBeat();

        void StopBeat();

        void Clear();

        std::vector<std::string> DeviceTypes(int* default_index = nullptr);

        std::vector<std::string> InputDeviceNames(int* default_index = nullptr);

        std::vector<std::string> OutputDeviceNames(int* default_index = nullptr);

        std::vector<int> SampleRates(int* default_index = nullptr);

        std::vector<int> BufferSizes(int* default_index = nullptr);

        bool UpdateDeviceType(int device_type_index);

        bool UpdateInputDevice(int input_device_index);

        bool UpdateOutputDevice(int output_device_index);

        bool UpdateSampleRate(int sample_rate_index);

        bool UpdateBufferSize(int buffer_size_index);

        void TapDown(int pitch);

        void TapUp(int pitch);

        void OnPlayProgressCallback(int play_index);

    private:
        AudioContext() = default;

        ~AudioContext() = default;

        void SetMidiInput(int index);

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

        // producer node
        Node::Ptr piano_node_;
        Node::Ptr oscillator_node_;

        int current_device_type_ = 0;

        juce::MidiKeyboardState keyboard_state_;
        int last_input_index_ = 0;
        bool is_adding_from_midi_input_ = false;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioContext)
    };
}

#endif //CHARACTER_AUDIO_CONTEXT_H
