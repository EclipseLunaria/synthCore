#pragma once
#include "osynth/ISynthComponent.h"
#include "osynth/config.h"

namespace OSynth::Core {
    
    enum class WaveShapes{
        Pulse,
        Sine,
        Saw,
        Triangle,
    };
    class Oscillator : public SynthComponent<Oscillator>{
        // properties
        float m_frequency = 0.0f;
        float m_phase = 0.0f;
        WaveShapes m_waveshape = WaveShapes::Sine;
        float m_pulse_width = 0.5f;
        float m_semitones = 0.0f;
        float m_cents = 0.0f;


        public:
        Oscillator(WaveShapes shape = WaveShapes::Sine, SynthComponent * parent = nullptr);

        float generateSample();
        float generateSample(float frequency);
        void writeSamplesToBuffer(float * buffer, int n);
        // static functions
        static float calculateWaveform(float phase, WaveShapes shape, float pulse_width);

        // property getters and setters
        WaveShapes getWaveshape();
        float getFrequency();
        float getPhase();
        float getPulseWidth();
        float getSemitones();
        float getCents();

        void setWaveshape(WaveShapes shape);
        void setFrequency(float frequency);
        void setPhase(float phase);
        void setPulseWidth(float pw_value);
        void setSemitones(float semitones);
        void setCents(float cents);

        bool usingGlobalSampleRate();
        // Synth Component Functions
        private:
        // helper functions
        float advancePhase(float frequency);
        float calculateTransposedFrequency(float frequency);
        void initializeImpl();
        void resetImpl();
        
    };
}