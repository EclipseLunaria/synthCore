#pragma once
#include "limits.h"
#include <numbers>
#include <string_view>
#include <cmath>
#ifndef DISABLED_THREADS
#include <thread>
#endif

#ifndef DISABLED_FILESYSTEM
#include <filesystem>
#endif

namespace OSynth::Core::Config{

const int BYTE = 1;
const int KILOBYTE = 1024;
const int MEGABYTE = 1024 * KILOBYTE;
// constant values


struct SynthConfig {
    std::string_view build_profile;
    int max_voices;
    int max_block_size;
    int wavetable_length;
    int oversampling_factor;
    int command_queue_size;
    int cache_line_size;
};

// forward declaration of get_build_profile
constexpr SynthConfig get_build_profile();

// create constant variables with the appropriate SynthConfig based on the build profile
#ifdef OSYNTH_MAX_VOICES
const int MAX_VOICES = MAX_VOICES;
#else
const int MAX_VOICES = get_build_profile().max_voices;
#endif

#ifdef OSYNTH_MAX_BLOCK_SIZE
const int MAX_BLOCK_SIZE = MAX_BLOCK_SIZE;
#else
const int MAX_BLOCK_SIZE = get_build_profile().max_block_size;
#endif

#ifdef OSYNTH_WAVETABLE_LENGTH
const int WAVETABLE_LENGTH = WAVETABLE_LENGTH;
#else
const int WAVETABLE_LENGTH = get_build_profile().wavetable_length;
#endif

#ifdef OSYNTH_OVERSAMPLING_FACTOR
const int OVERSAMPLING_FACTOR = OVERSAMPLING_FACTOR;
#else
const int OVERSAMPLING_FACTOR = get_build_profile().oversampling_factor;
#endif

#ifdef OSYNTH_COMMAND_QUEUE_SIZE
const int COMMAND_QUEUE_SIZE = COMMAND_QUEUE_SIZE;
#else
const int COMMAND_QUEUE_SIZE = get_build_profile().command_queue_size;
#endif

#ifdef OSYNTH_CACHE_LINE_SIZE
const int CACHE_LINE_SIZE = OSYNTH_CACHE_LINE_SIZE;
#else
const int CACHE_LINE_SIZE = get_build_profile().cache_line_size;
#endif

constexpr SynthConfig get_build_profile()
{
#ifndef OSYNTH_BUILD_PROFILE
#define OSYNTH_BUILD_PROFILE "full"
#endif

    constexpr std::string_view build_profile = OSYNTH_BUILD_PROFILE;
    if constexpr (build_profile == "lite"){
        return {
            .build_profile = std::string_view("lite"),
            .max_voices = 16,
            .max_block_size = 256,
            .wavetable_length = 512,
            .oversampling_factor = 1,
            .command_queue_size = 4 * KILOBYTE,
            .cache_line_size = 32
        };
    }
    else {
        return {
            .build_profile = std::string_view("full"),
            .max_voices = 64,
            .max_block_size = 1024,
            .wavetable_length = 1024,
            .oversampling_factor = 2,
            .command_queue_size = 1 * MEGABYTE,
            .cache_line_size = 64
        };
    }
}


int get_global_sample_rate();
void set_global_sample_rate(int sample_rate);

} // namespace OSynthCore::Config
