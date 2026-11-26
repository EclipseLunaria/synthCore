#include "osynth/parameter.h"

#include "osynth/utils.h"

#include <variant>
using namespace OSynth::Core;

using ParameterTypes = std::variant<Parameter>;

Parameter::Parameter(const char *name, float value, SynthNode *parent) : SynthNode(parent),
                                                                         m_value(value),
                                                                         m_default(value)
{
    Utils::string_copy(m_name, name, sizeof(m_name));
}

float OSynth::Core::Parameter::get()
{
    return m_value;
}

void OSynth::Core::Parameter::set(const float value)
{
    m_value = value;
}

std::string_view Parameter::getName()
{
    return std::string_view(m_name);
}

void OSynth::Core::Parameter::reset()
{
    m_value = m_default;
}
