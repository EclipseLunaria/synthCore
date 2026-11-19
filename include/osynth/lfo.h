#pragma once

#include "osynth/parameter.h"
#include "osynth/synthComponent.h"
#include "osynth/oscillator.h"
#include "osynth/oscillatorCore.h"

namespace OSynth::Core {
    class LFO : public SynthComponent<LFO> {
        friend class SynthComponent<LFO>;

        public:
        LFO(SynthComponent * parent);
        WaveShapes m_shape = WaveShapes::Sine;
        Parameter m_rate;
        bool m_trigger;
        bool m_envelope;

        private:

        void initializeImpl();
        void resetImpl();
        void updateImpl();

        OscillatorCore m_osc_core;
        
    };
}