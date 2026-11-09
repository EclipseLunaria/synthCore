#pragma once

#include "osynth/structures/SPSCQueue.h"
#include "osynth/config.h"
#include "osynth/gain.h"
#include "osynth/oscillator.h"

#include <optional>
#include <variant>

namespace OSynthCore
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

        using CommandQueue = OSynthCore::Structures::SPSCQueue<EngineEvents, 64>;
    }

    class OscillatorEngine
    {
        Oscillator m_oscillator;
        Gain m_gain;
        Commands::CommandQueue m_event_queue;

        float m_buffer[Config::get_build_profile().max_block_size];
        int m_sample_rate;

    public:
        OscillatorEngine(int sample_rate);

        Oscillator &get_oscillator();
        Gain &get_gain();
        Commands::CommandQueue &get_queue();
        float *get_buffer();

        float *render_buffer();
        float *render_buffer(size_t size);

        void process_events();
    };
}