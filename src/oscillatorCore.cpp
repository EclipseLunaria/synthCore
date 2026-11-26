#include "osynth/oscillatorCore.h"
using namespace OSynth::Core;

OSynth::Core::OscillatorCore::OscillatorCore(SynthNode *parent) : SynthNode(parent)
{
    m_frequency.set(0.0f);
    m_phase.set(0.0f);
    m_waveshape = WaveShapes::Sine;
}

OSynth::Core::OscillatorCore::OscillatorCore(float frequency, float phase, WaveShapes waveshape, SynthNode *parent) : SynthNode(parent)
{
    m_frequency.set(frequency);
    m_phase.set(phase);
    m_waveshape = waveshape;
}

void OscillatorCore::update()
{
    m_phase.set(advancePhase());
}

void OscillatorCore::initialize()
{
    m_phase.set(0.0f);
    m_waveshape = WaveShapes::Sine;
}

float OscillatorCore::advancePhase()
{
    float n_phase = m_phase.get() + (m_frequency.get() / getSampleRate());
    return n_phase - (int)n_phase;
}
