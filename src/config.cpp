#include "osynth/config.h"

namespace {
    int GLOBAL_SAMPLE_RATE = 44100;
}
using namespace OSynthCore::Config;

int OSynthCore::Config::get_global_sample_rate() {
    return GLOBAL_SAMPLE_RATE;
}
void OSynthCore::Config::set_global_sample_rate(int sample_rate){
    GLOBAL_SAMPLE_RATE = sample_rate;
}