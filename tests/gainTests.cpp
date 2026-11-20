#include <gtest/gtest.h>

#include "osynth/config.h"
#include "osynth/gain.h"
using namespace OSynth::Core;

TEST(GainTests, TestApplyGainToBuffer){
    Gain gain(0.0f);

    gain.initialize();

    ASSERT_EQ(gain.getLinearGain(), 1.0f);

    ASSERT_EQ(gain.getSampleRate(), Config::get_global_sample_rate());
    
    
}