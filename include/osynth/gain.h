#pragma once
#include "osynth/utils.h"
#include "osynth/smoothableFloat.h"

namespace OSynth::Core{

class Gain {
    
    int m_sample_rate;
    SmoothableFloat m_gain;

    const float smoothing_threshold = Utils::decibelToLinear(-18.0);

    public:
    Gain(float gain = 1, float smoothing_factor = 1.0, int sample_rate = 44100);
    
    void set_linear_gain(float gain);
    void set_gain_in_decibels(float gain);
    
    float get_linear_gain();
    float get_gain_in_decibels();

    void apply_gain_to_buffer(float *buffer, const int n_length);

};
}