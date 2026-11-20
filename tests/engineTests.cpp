#include <gtest/gtest.h>
#include "osynth/engine.h"
using namespace OSynth::Core;
TEST(EngineTests, TestEnginePublicMethods){
    // Test Base Constructor
    const auto SAMPLE_RATE = 48000;
    auto engine = OscillatorEngine(SAMPLE_RATE);
    ASSERT_EQ(engine.getSampleRate(), SAMPLE_RATE);

    auto &osc = engine.getOscillator();
    auto &gain = engine.getGain();
    auto &queue = engine.getQueue();

    float * buffer = engine.getBuffer();

    float * renderedBuffer = engine.renderBuffer();
    float * renderedSizeBuffer = engine.renderBuffer(Config::MAX_BLOCK_SIZE);

    engine.process_events();

}