#include "osynth/engine.h"
using namespace OSynthCore;
using namespace OSynthCore::Commands;

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

Oscillator &OscillatorEngine::get_oscillator() 
{
    return m_oscillator;
}

Gain &OscillatorEngine::get_gain()
{
    return m_gain;
}

Commands::CommandQueue &OscillatorEngine::get_queue()
{
    return m_event_queue;
}

float *OSynthCore::OscillatorEngine::get_buffer()
{
    return m_buffer;
}

float *OSynthCore::OscillatorEngine::render_buffer()
{
    size_t buffer_size = Config::MAX_BLOCK_SIZE;
    return render_buffer(buffer_size);
}

float *OSynthCore::OscillatorEngine::render_buffer(size_t size)
{
    m_oscillator.render_samples_to_buffer(m_buffer, size);
    m_gain.apply_gain_to_buffer(m_buffer, size);   
    return m_buffer;
}
void OSynthCore::OscillatorEngine::process_events()
{
    std::optional<EngineEvents> event;
    
    while((event = m_event_queue.pop()) != std::nullopt){
        if(!event.has_value()) continue;
        std::visit(overloaded{
            [&](SetFrequency c) {
                m_oscillator.set_frequency(c.frequency);
            },
            [&](SetWaveform c){
                m_oscillator.set_waveshape(c.waveshape);
            },
            [&](SetGain c){
                m_gain.set_linear_gain(c.gain);
            },
            [&](SetGainDecibels c){
                m_gain.set_gain_in_decibels(c.gain);
            },
            [&](SetPulseWidth c){
                m_oscillator.set_pulse_width(c.pw_value);
            },
            [&](SetSemitones c){
                m_oscillator.set_semitones(c.semitones);
            },
            [&](SetCents c){
                m_oscillator.set_cents(c.cents);
            }
        }, *event);
    }
}
