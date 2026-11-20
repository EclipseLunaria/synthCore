#include "osynth/engine.h"
using namespace OSynth::Core;
using namespace OSynth::Core::Commands;

namespace {
    template<class... Ts>
    struct overloaded : Ts... { using Ts::operator()...;};

    template<class... Ts>
    overloaded(Ts...) -> overloaded<Ts...>;
}

OscillatorEngine::OscillatorEngine(int sample_rate)
{
    this->m_sample_rate = sample_rate;
}

Oscillator &OscillatorEngine::getOscillator() 
{
    return m_oscillator;
}

Gain &OscillatorEngine::getGain()
{
    return m_gain;
}

Commands::CommandQueue &OscillatorEngine::getQueue()
{
    return m_event_queue;
}

float *OSynth::Core::OscillatorEngine::getBuffer()
{
    return m_buffer;
}

int OSynth::Core::OscillatorEngine::getSampleRate()
{
    return m_sample_rate;
}

float *OSynth::Core::OscillatorEngine::renderBuffer()
{
    size_t buffer_size = Config::MAX_BLOCK_SIZE;
    return renderBuffer(buffer_size);
}

float *OSynth::Core::OscillatorEngine::renderBuffer(size_t size)
{
    m_oscillator.writeSamplesToBuffer(m_buffer, size);
    m_gain.applyGainToBuffer(m_buffer, size);   
    return m_buffer;
}
void OSynth::Core::OscillatorEngine::process_events()
{
    std::optional<EngineEvents> event;
    
    while((event = m_event_queue.pop()) != std::nullopt){
        if(!event.has_value()) continue;
        std::visit(overloaded{
            [&](SetFrequency c) {
                m_oscillator.setFrequency(c.frequency);
            },
            [&](SetWaveform c){
                m_oscillator.setWaveshape(c.waveshape);
            },
            [&](SetGain c){
                m_gain.setLinearGain(c.gain);
            },
            [&](SetGainDecibels c){
                m_gain.setGainInDecibels(c.gain);
            },
            [&](SetPulseWidth c){
                m_oscillator.setPulseWidth(c.pw_value);
            },
            [&](SetSemitones c){
                m_oscillator.setSemitones(c.semitones);
            },
            [&](SetCents c){
                m_oscillator.setCents(c.cents);
            }
        }, *event);
    }
}
