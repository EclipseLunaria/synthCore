#pragma once
#include "osynth/config.h"

namespace OSynthCore {
    
    enum class WaveShapes{
        Pulse,
        Sine,
        Saw,
        Triangle,
    };
    class Oscillator {
        // properties
        WaveShapes m_waveshape = WaveShapes::Sine;
        float m_frequency = 0.0f;
        float m_phase = 0.0f;
        int m_sample_rate;
        float m_pulse_width = 0.5f;

        public:
        Oscillator(WaveShapes shape = WaveShapes::Sine, int sample_rate = Config::get_global_sample_rate());

        float render_sample();
        float render_sample(float frequency);

        // static functions
        static float evaluate_waveform(float phase, WaveShapes shape, float pulse_width);

        // property getters and setters
        WaveShapes get_waveshape();
        float get_frequency();
        float get_phase();
        int get_sample_rate();
        float get_pulse_width();

        void set_waveshape(WaveShapes shape);
        void set_frequency(float frequency);
        void set_phase(float phase);
        void set_sample_rate(int sample_rate);
        void set_pulse_width(float pw_value);

        private:
        // helper functions
        float advance_phase(float frequency);
        
    };
}