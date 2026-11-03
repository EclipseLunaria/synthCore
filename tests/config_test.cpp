#include <gtest/gtest.h>
#include <osynth/config.h>

TEST(ConfigTests, TestDefaultSampleRate){
    ASSERT_EQ(44100, OSynthCore::Config::get_global_sample_rate());
}