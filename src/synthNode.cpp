#include "osynth/synthNode.h"
#include "osynth/config.h"
using namespace OSynth::Core;
OSynth::Core::SynthNode::SynthNode(SynthNode *parent)
{
    m_parent = parent;
}

SynthNode *SynthNode::getParent()
{
    return nullptr;
}

int SynthNode::getSampleRate()
{
    return m_parent ? m_parent->getSampleRate() : Config::get_global_sample_rate();
}
