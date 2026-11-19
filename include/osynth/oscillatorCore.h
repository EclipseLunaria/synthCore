#pragma once
#include "osynth/parameter.h"
#include "osynth/synthComponent.h"
#include "osynth/synthNode.h"

namespace OSynth::Core{
    class OscillatorCore : public SynthComponent<OscillatorCore>, public SynthNode{
        friend class SynthComponent<OscillatorCore>;
        public:
        enum class WaveShapes{
            Pulse,
            Sine,
            Saw,
            Triangle,
        };

        OscillatorCore(SynthNode * parent = nullptr);
        OscillatorCore(float frequency, float phase = 0.0f, WaveShapes waveshape = WaveShapes::Sine, SynthNode * parent = nullptr);
        
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