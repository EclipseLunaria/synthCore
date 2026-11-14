#include <gtest/gtest.h>
#include <osynth/config.h>

TEST(ConfigTests, TestDefaultSampleRate){
    ASSERT_EQ(44100, OSynth::Core::Config::get_global_sample_rate());
}

TEST(ConfigTests, TestSetGlobalSampleRate){
    OSynth::Core::Config::set_global_sample_rate(48000);
    ASSERT_EQ(48000, OSynth::Core::Config::get_global_sample_rate());
}