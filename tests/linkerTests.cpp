#include <gtest/gtest.h>

#include "osynth/config.h"
#include "osynth/engine.h"
#include "osynth/gain.h"
#include "osynth/oscillator.h"
#include "osynth/oscillatorCore.h"
#include "osynth/parameter.h"
#include "osynth/smoothableFloat.h"
#include "osynth/synthNode.h"
#include "osynth/smoothableFloat.h"
#include "osynth/synthNode.h"
#include "osynth/structures/HistoryQueue.h"
#include "osynth/structures/SPSCQueue.h"

using namespace OSynth::Core;

TEST(LinkerTests, TestAllPublicClassesLinkage){
    auto engine = OscillatorEngine(48000);
    engine.getSampleRate();

    auto gain = Gain();
    gain.setLinearGain(.5f);

    auto osc = Oscillator();
    osc.setCents(3);
    osc.setFrequency(440);

    auto osc_core = OscillatorCore(440);
    osc_core.getParent();
    osc_core.initialize();

    auto parameter = Parameter("param", .5f, nullptr);
    ASSERT_EQ(parameter.getName(), "param");

    auto sfloat = SmoothableFloat(.5);
    ASSERT_EQ(sfloat.get_current(), .5f);

    auto synthNode = SynthNode(nullptr);
    synthNode.initialize();
    synthNode.getParent();

    auto voice = SynthVoice();
    voice.initialize();
}