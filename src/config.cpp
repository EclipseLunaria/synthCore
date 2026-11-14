#include "osynth/config.h"

namespace {
    int GLOBAL_SAMPLE_RATE = 44100;
}
using namespace OSynth::Core::Config;

int OSynth::Core::Config::get_global_sample_rate() {
    return GLOBAL_SAMPLE_RATE;
}
void OSynth::Core::Config::set_global_sample_rate(int sample_rate){
    GLOBAL_SAMPLE_RATE = sample_rate;
}