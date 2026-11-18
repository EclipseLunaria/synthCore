#pragma once
#include <cstdint>
#include <string_view>
namespace OSynth::Core{

    class Parameter{
        public:
        struct ParameterInfo {
            float value = 1.0f;
            float default_value = 1.0f;
            float max_value = 1.0f;
            float min_value = 0.0f;
        };
        Parameter(const char * name, const ParameterInfo values);
        std::string_view getName();
       
        private:
        float m_value;
        char m_name[16];
        uint16_t param_id;
        const ParameterInfo m_default_values;
    };

}