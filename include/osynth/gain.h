#pragma once
#include "osynth/utils.h"
#include "osynth/smoothableFloat.h"
#include "osynth/ISynthComponent.h"
namespace OSynth::Core{

class Gain : public SynthComponent<Gain>{
    friend class SynthComponent<Gain>;

    SmoothableFloat m_gain;
    const float smoothing_threshold = Utils::decibelToLinear(-18.0);

    public:
    Gain(float gain = 1, float smoothing_factor = 1.0, SynthComponent * parent = nullptr);
    
    void set_linear_gain(float gain);
    void set_gain_in_decibels(float gain);
    
    float get_linear_gain();
    float get_gain_in_decibels();

    void apply_gain_to_buffer(float *buffer, const int n_length);

    void initializeImpl();
    void resetImpl();
};
}