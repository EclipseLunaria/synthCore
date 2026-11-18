#include "osynth/parameter.h"
#include <cstring>
using namespace OSynth::Core;

Parameter::Parameter(const char *name, const ParameterInfo values) :
m_default_values(values),
m_value(values.default_value)
{
    strcpy(m_name, name);
}

std::string_view OSynth::Core::Parameter::getName()
{
    return std::string_view();
}
