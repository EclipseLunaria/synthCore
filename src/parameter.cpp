#include "osynth/parameter.h"
#include <cstring>
using namespace OSynth::Core;

Parameter::Parameter(const char *name, float value):
m_value(value),
m_default(value)
{
    strncpy(m_name, name, sizeof(m_name));
}

std::string_view Parameter::getName()
{
    return std::string_view();
}
