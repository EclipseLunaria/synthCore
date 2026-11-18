#pragma once
#include "osynth/ISynthComponent.h"
#include "osynth/oscillator.h"
#include "osynth/gain.h"

namespace OSynth::Core{
    class SynthVoice : public SynthComponent<SynthVoice> {
        friend class SynthComponent<SynthVoice>;
        public: 
        SynthVoice();

        private:
        Oscillator m_osc;
        Gain m_gain;

        protected:
        void resetImpl();
        void initializeImpl();
        
    };
}