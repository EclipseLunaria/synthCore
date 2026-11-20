#pragma once

#include <cstdint>
#include <string_view>
#include <array>

#include "osynth/synthNode.h"

namespace OSynth::Core
{
    class Parameter : public SynthNode
    {
    public:
        Parameter(const char *name, float value = 1.0f, SynthNode *parent = nullptr);

        float get();
        void set(const float value);
        std::string_view getName();
        void reset();

    private:
        float m_value;
        const float m_default;
        char m_name[16];
    };

    template <size_t Size>
    class ParameterList
    {

    public:
        ParameterList(Parameter **parameters, size_t length);
        Parameter *getParameter(uint16_t id);
        Parameter *getParameter(const char *name);

    private:
        std::array<Parameter *, Size> m_parameters = {nullptr};
        size_t m_length;
    };

}