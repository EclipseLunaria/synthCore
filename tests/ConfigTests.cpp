#include <gtest/gtest.h>
#include <osynth/config.h>

TEST(ConfigTests, TestDefaultSampleRate){
    ASSERT_EQ(44100, OSynthCore::Config::get_global_sample_rate());
}

TEST(ConfigTests, TestSetGlobalSampleRate){
    OSynthCore::Config::set_global_sample_rate(48000);
    ASSERT_EQ(48000, OSynthCore::Config::get_global_sample_rate());
}