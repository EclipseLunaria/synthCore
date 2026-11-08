#pragma once
#include <cmath>
#include <iostream>
#include <bit>
#include <cstring>
#include <array>

namespace OSynthUtils {

    inline float clipSample(float s) {
        if (s > 1.0f) s = 1.0f;
        if (s < -1.0f) s = -1.0f;
        return s;
    }

    inline float linearToDecibel(float linear) {
        return 20.0f * log10f(linear);
    }

    inline float decibelToLinear(float decibel) {
        return powf(10.0f, decibel / 20.0f);
    }

    template <typename T>
    constexpr T swap_bytes(T val) noexcept {
        static_assert(std::is_trivially_copyable_v<T>, "Type must be trivially copyable.");

        auto representation = std::bit_cast<std::array<std::byte, sizeof(T)>>(val);

        for (size_t i = 0; i < sizeof(T)/2; ++i){
            std::swap(representation[i], representation[sizeof(T)-1-i]);
        }
        return std::bit_cast<T>(representation);
    }

    template <typename T>
    constexpr T to_little_endian(T val) noexcept {
        if constexpr (std::endian::native == std::endian::little){
            return val;
        }
        else if constexpr (std::endian::native == std::endian::big){
            return swap_bytes(val);
        }
        else {
            static_assert(
                std::endian::native == std::endian::little || std::endian::native == std::endian::big,
                "unsupported mixed endian architecture"
            );
        }
    }
    template <typename T>
    constexpr T to_little_endian(T val, char * buffer, size_t size){
        T value = to_little_endian(val);
        
        memcpy(buffer, (char *)&value, size);
        return value;
    }


}