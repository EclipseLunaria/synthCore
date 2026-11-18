#include "osynth/gain.h"
#include "osynth/utils.h"
using namespace OSynth::Core;

Gain::Gain(float gain, float smoothing_factor, SynthComponent * parent):
SynthComponent<Gain>(parent),
m_gain(gain, smoothing_factor)
{
}

void Gain::set_linear_gain(float gain)
{
    m_gain.set(gain);
}

void Gain::set_gain_in_decibels(float decibel)
{
    set_linear_gain(Utils::decibelToLinear(decibel));
    
}

float Gain::get_linear_gain()
{
    return m_gain.get_current();
}

float Gain::get_gain_in_decibels()
{
    return Utils::linearToDecibel(get_linear_gain());
}

void Gain::apply_gain_to_buffer(float *buffer, const int n_length)
{
    for (int i = 0; i < n_length; i++){
        buffer[i] *= m_gain.next(getSampleRate());
    }
}

void Gain::initializeImpl()
{
    m_gain.set_current(1.0f);
    m_gain.set_target(1.0f);
}

void Gain::resetImpl()
{
}
