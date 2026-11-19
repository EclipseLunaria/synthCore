#include "osynth/lfo.h"
using namespace OSynth::Core;
OSynth::Core::LFO::LFO(SynthNode *parent):
SynthNode(parent)
{

}
void OSynth::Core::LFO::initializeImpl()
{
    m_osc_core.initialize();
}
void OSynth::Core::LFO::updateImpl()
{
    m_osc_core.update();
    // advance phase
    
}