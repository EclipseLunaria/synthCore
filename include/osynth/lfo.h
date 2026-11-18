#pragma once

#include "osynth/parameter.h"
#include "osynth/ISynthComponent.h"
#include "osynth/oscillator.h"

namespace OSynth::Core {
    class LFO : SynthComponent<LFO> {
        friend class SynthComponent<LFO>;

        public:
        WaveShapes m_shape = WaveShapes::Sine;
        Parameter m_rate;
        bool m_trigger;
        bool m_envelope;


        void initializeImpl();
        void resetImpl();

        void updateImpl();
    };
}