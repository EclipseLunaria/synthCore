#pragma once
#include "osynth/parameter.h"
#include "osynth/synthNode.h"

namespace OSynth::Core{
    class OscillatorCore : public SynthNode{
        public:
        enum class WaveShapes{
            Pulse,
            Sine,
            Saw,
            Triangle,
        };

        OscillatorCore(SynthNode * parent = nullptr);
        OscillatorCore(float frequency, float phase = 0.0f, WaveShapes waveshape = WaveShapes::Sine, SynthNode * parent = nullptr);
        
        virtual void update() override;
        virtual void initialize() override;

        private:
        float advancePhase();

        Parameter m_frequency = Parameter("frequency", 0.0f);
        Parameter m_phase = Parameter("phase", 0.0f);

        WaveShapes m_waveshape = WaveShapes::Sine;
    };
}