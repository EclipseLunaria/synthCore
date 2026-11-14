#include <gtest/gtest.h>
#include "osynth/oscillator.h"
#include "osynth/config.h"
using namespace OSynth::Core;

int countZeroCrossings(float *buffer, int n){
    int zero_crossings = 0;
    for (int i = 1; i < n; ++i){
        if ((buffer[i - 1] >= 0 && buffer[i] < 0) || (buffer[i - 1] < 0 && buffer[i] >= 0)) {
            ++zero_crossings;
            std::cout << "Zero crossing at index " << i << ": ";
            std::cout << buffer[i - 1] << " " << buffer[i] << std::endl;
        }
    }
    return zero_crossings;
}
TEST(OscillatorTest, testRenderSampleToBuffer){
    // variables
    const int frequency = 440;
    const int sample_rate = 44100;
    const int buffer_size = 1000;
    float buffer[buffer_size];
    
    Oscillator osc = Oscillator(WaveShapes::Sine, sample_rate);
    osc.set_frequency(440);
    osc.render_samples_to_buffer(buffer, buffer_size);

    // Count zero crossings in the buffer
    int zero_crossings = countZeroCrossings(buffer, buffer_size);
    /*int expected_crossings = 0;
    for (int i = 1; i < buffer_size; ++i) {
        if ((buffer[i - 1] >= 0 && buffer[i] < 0) || (buffer[i - 1] < 0 && buffer[i] >= 0)) {
            ++expected_crossings;
            std::cout << "Zero crossing at index " << i << ": ";
            std::cout << buffer[i - 1] << " " << buffer[i] << std::endl;
        }
    }*/
    ASSERT_EQ(zero_crossings, 20);
}

TEST(OscillatorTest, testRenderSampleWithSemitones){
    Oscillator osc = Oscillator(WaveShapes::Sine, 44100);
    osc.set_frequency(440);
    osc.set_semitones(12);
    osc.set_cents(50);
    float sample = osc.render_sample();
    ASSERT_NE(sample, 0);

    
}

TEST(OscillatorTest, testCountZeroCrossingsWithSemitoneShift){
    int sample_rate = 44100;
    int n = 1000;
    float buffer[n];
    float buffer2[n];
    Oscillator osc = Oscillator(WaveShapes::Sine, sample_rate);
    Oscillator osc2 = Oscillator(WaveShapes::Sine, sample_rate);

    osc.set_frequency(440);
    osc2.set_frequency(440);

    osc2.set_semitones(12);

    osc.render_samples_to_buffer(buffer, n);
    osc2.render_samples_to_buffer(buffer2, n);

    int crossings1 = countZeroCrossings(buffer, n);
    int crossings2 = countZeroCrossings(buffer2, n);

    ASSERT_NE(crossings1, crossings2);

    ASSERT_EQ(crossings1, 20);

    // crossings should be twice as much since it is a whole octive higher
    ASSERT_EQ(crossings2, 40);

}