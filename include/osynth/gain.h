#pragma once

namespace OSynthCore{

class Gain {
    private:
   
    float m_gain = 1; // linear value for gain
    int m_sample_rate;

    public:
    Gain(float gain = 1, float time_constant = 1.0, int sample_rate = 44100);
    
    void set_linear_gain(float gain);
    void set_gain_in_decibels(float gain);
    
    float get_linear_gain();
    float get_gain_in_decibels();

    void apply_gain_to_buffer(float *buffer, const int n_length);

};
}