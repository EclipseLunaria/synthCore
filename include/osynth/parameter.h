#pragma once
#include <cstdint>
#include <string_view>
namespace OSynth::Core{

    class Parameter{
        float m_value;
        char name[16];
        uint16_t param_id;
        public:
        Parameter(const char * name, float value = 1);
       
        
        std::string_view getName();
    };

}