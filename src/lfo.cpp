#include "osynth/lfo.h"
using namespace OSynth::Core;
OSynth::Core::LFO::LFO(SynthComponent *parent):
SynthComponent(parent)
{
    m_osc_core = OscillatorCore(this);
}
void OSynth::Core::LFO::updateImpl()
{
    // advance phase
    
}