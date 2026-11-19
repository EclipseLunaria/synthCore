#include "osynth/parameter.h"
#include <cstring>
using namespace OSynth::Core;

Parameter::Parameter(const char *name, float value):
m_value(value),
m_default(value)
{
    strncpy(m_name, name, sizeof(m_name));
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
