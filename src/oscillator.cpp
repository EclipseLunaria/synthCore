#include "osynth/oscillator.h"
#include "osynth/config.h"
#include <numbers>

using namespace OSynth::Core;
Oscillator::Oscillator(WaveShapes shape, SynthNode * parent)
: SynthNode(parent), m_waveshape(shape)
{
}


float Oscillator::generateSample(){
    // apply modifiers such as lfos
    //advance phase
    return generateSample(m_frequency.get());
}

float Oscillator::generateSample(float frequency){
    // apply modifiers
    frequency = calculateTransposedFrequency(frequency);
    
    m_phase.set(advancePhase(frequency));
    
    return calculateWaveform(m_phase.get(), m_waveshape, m_pulse_width.get());
}

void Oscillator::writeSamplesToBuffer(float *buffer, int n)
{
    for (int i = 0; i < n; ++i){
        buffer[i] = generateSample();
    }
}

WaveShapes Oscillator::getWaveshape()
{
    return m_waveshape;
}

float Oscillator::getFrequency()
{
    return m_frequency.get();
}

float Oscillator::getPhase()
{
    return m_phase.get();
}

float Oscillator::getPulseWidth(){
    return m_pulse_width.get();
}

float Oscillator::getSemitones()
{
    return m_semitones.get();
}

float Oscillator::getCents()
{
    return m_cents.get();
}

void Oscillator::setWaveshape(WaveShapes shape)
{
    m_waveshape = shape;
}

void Oscillator::setFrequency(float frequency)
{
    m_frequency.set(frequency);
}

void Oscillator::setPhase(float phase)
{
    m_phase.set(phase);
}

void Oscillator::setPulseWidth(float pw_value){
    if (pw_value <= 0) m_pulse_width.set(0.0f);
    else if (pw_value >= 1.0f) m_pulse_width.set(1.0f);
    else m_pulse_width.set(pw_value);
}

void Oscillator::setSemitones(float semitones)
{
    m_semitones.set(semitones);
}

void Oscillator::setCents(float cents)
{
    m_cents.set(cents);
}

bool OSynth::Core::Oscillator::usingGlobalSampleRate()
{
    return getParent() == nullptr;
}

void OSynth::Core::Oscillator::initialize()
{
    m_cents.set(0);
    m_semitones.set(0);
    m_frequency.set(0);
    m_pulse_width.set(.5f);
    m_phase.set(0.0f);
    m_waveshape = WaveShapes::Sine;
}

void Oscillator::reset()
{
    initialize();
}

// Translation unit constants
namespace {
    const float TWO_PI = std::numbers::pi_v<float>;
}

/*
Helper Functions supporting main functionality
*/
float Oscillator::advancePhase(float frequency)
{
    return fmodf(m_phase.get() + frequency / getSampleRate(), 1.0f);
}

float Oscillator::calculateTransposedFrequency(float frequency)
{
    return frequency * powf(2.0f, (m_semitones.get() + m_cents.get() / 100.0f)/12.0f);
}

float Oscillator::calculateWaveform(float phase, WaveShapes shape, float pulse_width = 0.0f)
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