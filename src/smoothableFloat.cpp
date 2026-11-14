#include "osynth/smoothableFloat.h"
using namespace OSynth::Core;
SmoothableFloat::SmoothableFloat(float f, float smoothing_factor) :
    m_current_value(f),
    m_target_value(f),
    m_smoothing_factor(smoothing_factor)
{
}

void SmoothableFloat::set(const float f)
{
    m_target_value = f;
}

float SmoothableFloat::get_target() const
{
    return m_target_value;
}

float SmoothableFloat::get_current() const
{
    return m_current_value;
}

void SmoothableFloat::set_smoothing_factor(const float ms)
{
    m_smoothing_factor = ms;
}

float SmoothableFloat::get_smoothing_factor() const
{
    return m_smoothing_factor;
}

float SmoothableFloat::next(int sample_rate)
{
    if (!is_smoothing()) return m_target_value;

    float a = 1.0f - expf(-1.0f/(m_smoothing_factor*sample_rate));
    float ret = m_current_value - (a * (m_target_value - m_current_value));
    m_current_value = ret;
    return ret;
}

SmoothableFloat &SmoothableFloat::operator=(const float other)
{
    this->m_current_value = other;
    this->m_target_value = other;
    return *this;  
    // TODO: insert return statement here
}

// used to short-circuit computation when current gain is sufficiently close to the target gain
bool SmoothableFloat::is_smoothing()
{
    return fabsf(m_target_value - m_current_value) < SMOOTHING_THRESHOLD;
}
