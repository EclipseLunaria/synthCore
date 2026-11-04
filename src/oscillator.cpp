#include "osynth/oscillator.h"
#include "osynth/config.h"
#include <numbers>

using namespace OSynthCore;
Oscillator::Oscillator(WaveShapes shape, int sample_rate)
: m_sample_rate(sample_rate), m_waveshape(shape)
{
}


float Oscillator::render_sample(){
    // apply modifiers such as lfos
    //advance phase
    return render_sample(m_frequency);
}

float Oscillator::render_sample(float frequency){
    // apply modifiers
    frequency = transpose_frequency(frequency);
    
    m_phase = advance_phase(frequency);
    
    return evaluate_waveform(m_phase, m_waveshape, m_pulse_width);
}

void Oscillator::render_samples_to_buffer(float *buffer, int n)
{
    for (int i = 0; i < n; ++i){
        buffer[i] = render_sample();
    }
}

WaveShapes Oscillator::get_waveshape()
{
    return m_waveshape;
}

float Oscillator::get_frequency()
{
    return m_frequency;
}

float Oscillator::get_phase()
{
    return m_phase;
}

int Oscillator::get_sample_rate()
{
    return m_sample_rate;
}

float Oscillator::get_pulse_width(){
    return m_pulse_width;
}

float Oscillator::get_semitones()
{
    return m_semitones;
}

float Oscillator::get_cents()
{
    return m_cents;
}

void Oscillator::set_waveshape(WaveShapes shape)
{
    m_waveshape = shape;
}

void Oscillator::set_frequency(float frequency)
{
    m_frequency = frequency;
}

void Oscillator::set_phase(float phase)
{
    m_phase = phase;
}

void Oscillator::set_sample_rate(int sample_rate){
    m_sample_rate = sample_rate;
}

void Oscillator::set_pulse_width(float pw_value){
    if (pw_value <= 0) m_pulse_width = 0.0f;
    else if (pw_value >= 1.0f) m_pulse_width = 1.0f;
    else m_pulse_width = pw_value;
}

void Oscillator::set_semitones(float semitones)
{
    m_semitones = semitones;
}

void Oscillator::set_cents(float cents)
{
    m_cents = cents;
}

// Translation unit constants
namespace {
    const float TWO_PI = std::numbers::pi_v<float>;
}

/*
Helper Functions supporting main functionality
*/
float OSynthCore::Oscillator::advance_phase(float frequency)
{
    return fmodf(m_phase + frequency / m_sample_rate, 1.0f);
}

float OSynthCore::Oscillator::transpose_frequency(float frequency)
{
    return frequency * powf(2.0f, (m_semitones + m_cents / 100.0f)/12.0f);
}

float OSynthCore::Oscillator::evaluate_waveform(float phase, WaveShapes shape, float pulse_width = 0.0f)
{
    switch (shape){
        case WaveShapes::Sine:
        return 2 * sinf(TWO_PI * phase) - 1;

        case WaveShapes::Saw:
        return 2 * phase - 1;

        case WaveShapes::Triangle:
        return phase < .5 
                ? 4 * phase - 1
                : 3 - 4 * phase;

        case WaveShapes::Pulse:
        return phase < pulse_width ? 1 : -1;

        default:
        return 0;
    }
}