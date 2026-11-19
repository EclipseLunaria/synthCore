#include "osynth/lfo.h"
using namespace OSynth::Core;
OSynth::Core::LFO::LFO(SynthNode *parent):
SynthNode(parent)
{

}
void OSynth::Core::LFO::initialize()
{
    m_osc_core.initialize();
}
void OSynth::Core::LFO::update()
{
    m_osc_core.update();
    // advance phase
    
}