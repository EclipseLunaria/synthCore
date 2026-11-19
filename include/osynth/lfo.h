#pragma once

#include "osynth/parameter.h"
#include "osynth/synthNode.h"
#include "osynth/oscillator.h"
#include "osynth/oscillatorCore.h"

namespace OSynth::Core {
    class LFO : public SynthNode {

        public:
        LFO(SynthNode * parent);
        WaveShapes m_shape = WaveShapes::Sine;
        Parameter m_rate = Parameter("rate", 1.0f);
        bool m_trigger = false;
        bool m_envelope = false;

        virtual void initialize() override;
        virtual void reset() override;
        virtual void update() override;
        private:


        OscillatorCore m_osc_core;
        
    };
}