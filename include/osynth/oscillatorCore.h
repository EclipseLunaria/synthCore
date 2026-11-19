#pragma once
#include "osynth/parameter.h"
#include "osynth/synthComponent.h"

namespace OSynth::Core{
    class OscillatorCore : public SynthComponent<OscillatorCore>{
        friend class SynthComponent<OscillatorCore>;
        public:
        enum class WaveShapes{
            Pulse,
            Sine,
            Saw,
            Triangle,
        };

        OscillatorCore(SynthComponent * parent = nullptr);
        OscillatorCore(float frequency, float phase = 0.0f, WaveShapes waveshape = WaveShapes::Sine, SynthComponent * parent = nullptr);
        
        private:
        void updateImpl();
        void resetImpl();
        void initializeImpl();        
        float advancePhase();

        Parameter m_frequency = Parameter("frequency", 0.0f);
        Parameter m_phase = Parameter("phase", 0.0f);

        WaveShapes m_waveshape = WaveShapes::Sine;

    };
}