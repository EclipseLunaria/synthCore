#include "osynth/gain.h"
#include "osynth/utils.h"
using namespace OSynth::Core;

Gain::Gain(float gain, float smoothing_factor, SynthNode * parent):
SynthNode(parent),
m_gain(gain, smoothing_factor)
{
}

void Gain::setLinearGain(float gain)
{
    m_gain.set(gain);
}

void Gain::setGainInDecibels(float decibel)
{
    setLinearGain(Utils::decibelToLinear(decibel));
    
}

float Gain::getLinearGain()
{
    return m_gain.get_current();
}

float Gain::getGainInDecibels()
{
    return Utils::linearToDecibel(getLinearGain());
}

void Gain::applyGainToBuffer(float *buffer, const int n_length)
{
    for (int i = 0; i < n_length; i++){
        buffer[i] *= m_gain.next(getSampleRate());
    }
}

void Gain::initialize()
{
    m_gain.set_current(1.0f);
    m_gain.set_target(1.0f);
}

void Gain::reset()
{
}
