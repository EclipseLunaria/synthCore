#pragma once

#include "osynth/synthNode.h"
#include "osynth/voice.h"

#include "osynth/structures/SPSCQueue.h"
#include "osynth/config.h"
#include "osynth/gain.h"
#include "osynth/oscillator.h"

#include <variant>

namespace OSynth::Core
{

    namespace Commands
    {

        // CONSTANTS

        struct SetFrequency
        {
            float frequency;
        };

        struct SetWaveform
        {
            WaveShapes waveshape;
        };

        struct SetGain
        {
            float gain;
        };

        struct SetGainDecibels {
            float gain;
        };

        struct SetPulseWidth
        {
            float pw_value;
        };

        struct SetSemitones{
            float semitones;
        };

        struct SetCents{
            float cents;
        };
        
        using EngineEvents = std::variant<
            SetFrequency,
            SetWaveform,
            SetGain,
            SetGainDecibels,
            SetPulseWidth,
            SetSemitones,
            SetCents
            >;

        using CommandQueue = OSynth::Core::Structures::SPSCQueue<EngineEvents, 64>;
    }

    class OscillatorEngine
    {
        Oscillator m_oscillator;
        Gain m_gain;
        Commands::CommandQueue m_event_queue;

        // TODO: Refactor buffer into audio buffer class
        // which will support multiple channels.
        float m_buffer[Config::MAX_BLOCK_SIZE];
        int m_sample_rate;

    public:
        OscillatorEngine(int sample_rate);

        Oscillator &getOscillator();
        Gain &getGain();
        Commands::CommandQueue &getQueue();
        float *getBuffer();
        int getSampleRate();

        float *renderBuffer();
        float *renderBuffer(size_t size);

        void process_events();
    };
}