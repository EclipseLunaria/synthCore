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
        int m_sample_rate;
        float m_frequency = 0.0f;
        float m_phase = 0.0f;
        WaveShapes m_waveshape = WaveShapes::Sine;
        float m_pulse_width = 0.5f;
        float m_semitones = 0.0f;
        float m_cents = 0.0f;


        public:
        Oscillator(WaveShapes shape = WaveShapes::Sine, int sample_rate = Config::get_global_sample_rate());

        float render_sample();
        float render_sample(float frequency);
        void render_samples_to_buffer(float * buffer, int n);
        // static functions
        static float evaluate_waveform(float phase, WaveShapes shape, float pulse_width);

        // property getters and setters
        WaveShapes get_waveshape();
        float get_frequency();
        float get_phase();
        int get_sample_rate();
        float get_pulse_width();
        float get_semitones();
        float get_cents();

        void set_waveshape(WaveShapes shape);
        void set_frequency(float frequency);
        void set_phase(float phase);
        void set_sample_rate(int sample_rate);
        void set_pulse_width(float pw_value);
        void set_semitones(float semitones);
        void set_cents(float cents);

        private:
        // helper functions
        float advance_phase(float frequency);
        float transpose_frequency(float frequency);
        
    };
}