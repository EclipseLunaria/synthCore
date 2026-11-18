#pragma once
#include "osynth/ISynthComponent.h"
#include "osynth/oscillator.h"
#include "osynth/gain.h"

namespace OSynth::Core{
    class SynthVoice : public SynthComponent<SynthVoice> {
        public: 
        SynthVoice();
        void initialize();
        void reset();

        private:
        Oscillator m_osc;
        Gain m_gain;

        void updateImpl();
        void initializeImpl();
        
    };
}