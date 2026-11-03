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

namespace OSynthCore::Config{

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
};

// forward declaration of get_build_profile
constexpr SynthConfig get_build_profile();

// create constant variables with the appropriate SynthConfig based on the build profile
#ifdef MAX_VOICES
const int MAX_VOICES = MAX_VOICES;
#else
const int MAX_VOICES = get_build_profile().max_voices;
#endif

#ifdef MAX_BLOCK_SIZE
const int MAX_BLOCK_SIZE = MAX_BLOCK_SIZE;
#else
const int MAX_BLOCK_SIZE = get_build_profile().max_block_size;
#endif

#ifdef WAVETABLE_LENGTH
const int WAVETABLE_LENGTH = WAVETABLE_LENGTH;
#else
const int WAVETABLE_LENGTH = get_build_profile().wavetable_length;
#endif

#ifdef OVERSAMPLING_FACTOR
const int OVERSAMPLING_FACTOR = OVERSAMPLING_FACTOR;
#else
const int OVERSAMPLING_FACTOR = get_build_profile().oversampling_factor;
#endif

#ifdef COMMAND_QUEUE_SIZE
const int COMMAND_QUEUE_SIZE = COMMAND_QUEUE_SIZE
#else
const int COMMAND_QUEUE_SIZE = get_build_profile().command_queue_size;
#endif


constexpr SynthConfig get_build_profile()
{
#ifndef BUILD_PROFILE
    #define BUILD_PROFILE "full"
    #endif

    constexpr std::string_view build_profile = BUILD_PROFILE;
    if constexpr (build_profile == "lite"){
        return {
            .build_profile = std::string_view("lite"),
            .max_voices = 16,
            .max_block_size = 256,
            .wavetable_length = 512,
            .oversampling_factor = 1,
            .command_queue_size = 4 * KILOBYTE
        };
    }
    else if constexpr (build_profile == "custom"){
        return {
            .build_profile = std::string_view("custom"),
            #ifndef MAX_VOICES
            .max_voices = 16,
            #else
            .max_voices = MAX_VOICES,
            #endif
            #ifndef MAX_BLOCK_SIZE
            .max_block_size = 1024,
            #else
            .max_block_size = MAX_BLOCK_SIZE,
            #endif
            #ifndef WAVETABLE_LENGTH
            .wavetable_length = 1024,
            #else
            .wavetable_length = WAVETABLE_LENGTH,
            #endif
            #ifndef OVERSAMPLING_FACTOR
            .oversampling_factor = 2,
            #else
            .oversampling_factor = OVERSAMPLING_FACTOR
            #endif
            #ifndef COMMAND_QUEUE_SIZE
            .command_queue_size = 1 * MEGABYTE
            #else
            .command_queue_size = COMMAND_QUEUE_SIZE
            #endif

        };
    }
    else {
        return {
            .build_profile = std::string_view("full"),
            .max_voices = 64,
            .max_block_size = 1024,
            .wavetable_length = 1024,
            .oversampling_factor = 2,
            .command_queue_size = 1 * MEGABYTE
        };
    }
}


int get_global_sample_rate();
void set_global_sample_rate(int sample_rate);

} // namespace OSynthCore::Config
