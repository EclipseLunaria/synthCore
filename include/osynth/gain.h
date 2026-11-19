#pragma once

#include "osynth/smoothableFloat.h"
#include "osynth/synthComponent.h"
#include "osynth/synthNode.h"
#include "osynth/utils.h"

namespace OSynth::Core{

class Gain : public SynthNode{

    SmoothableFloat m_gain;
    const float smoothing_threshold = Utils::decibelToLinear(-18.0);

    public:
    Gain(float gain = 1, float smoothing_factor = 1.0, SynthNode * parent = nullptr);
    
    void setLinearGain(float gain);
    void setGainInDecibels(float gain);
    
    float getLinearGain();
    float getGainInDecibels();

    void applyGainToBuffer(float *buffer, const int n_length);

    void initialize();
    void reset();
};
}