#pragma once
#include "osynth/oscillator.h"
#include "osynth/gain.h"

namespace OSynth::Core
{
    class SynthVoice : public SynthNode
    {
    public:
        SynthVoice();

        virtual void reset() override;
        virtual void initialize() override;

    private:
        Oscillator m_osc;
        Gain m_gain;
    };
}