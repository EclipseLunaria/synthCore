#pragma once
#include "osynth/synthNode.h"
#include "osynth/parameter.h"
#include "osynth/config.h"

namespace OSynth::Core {
    
    enum class WaveShapes{
        Pulse,
        Sine,
        Saw,
        Triangle,
    };
    class Oscillator : public SynthNode{
        // properties
        Parameter m_frequency = Parameter("frequency", 0.0f);
        Parameter m_phase = Parameter("phase", 0.0f);
        Parameter m_pulse_width = Parameter("pulse_width", 0.5f);
        Parameter m_semitones = Parameter("semitones", 0.0f);
        Parameter m_cents = Parameter("cents", 0.0f);

        WaveShapes m_waveshape = WaveShapes::Sine;

        public:
        Oscillator(WaveShapes shape = WaveShapes::Sine, SynthNode * parent = nullptr);

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
        virtual void initialize() override;
        virtual void reset() override;
        private:
        // helper functions
        float advancePhase(float frequency);
        float calculateTransposedFrequency(float frequency);

        
    };
}