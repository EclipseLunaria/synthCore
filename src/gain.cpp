#include "osynth/gain.h"
#include "osynth/utils.h"
using namespace OSynthCore;
OSynthCore::Gain::Gain(float gain, float smoothing_factor, int sample_rate):
m_sample_rate(sample_rate),
m_gain(gain, smoothing_factor)
{
}

void Gain::set_linear_gain(float gain)
{
    m_gain.set(gain);
}

void Gain::set_gain_in_decibels(float decibel)
{
    set_linear_gain(OSynthUtils::decibelToLinear(decibel));
    
}

float OSynthCore::Gain::get_linear_gain()
{
    return m_gain.get_current();
}

float OSynthCore::Gain::get_gain_in_decibels()
{
    return OSynthUtils::linearToDecibel(get_linear_gain());
}

void OSynthCore::Gain::apply_gain_to_buffer(float *buffer, const int n_length)
{
    for (int i = 0; i < n_length; i++){
        buffer[i] *= m_gain.next(m_sample_rate);
    }
}
