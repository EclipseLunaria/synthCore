#pragma once
#include <cstdint>
#include <string_view>
#include <array>
namespace OSynth::Core{

    class Parameter {
        public:
        Parameter(const char * name, float value = 1.0f);
        
        
        std::string_view getName();
        float get(){
            return m_value;
        }
        void set(const float value) {
            m_value = value;
        }
        private:
        float m_value;
        const float m_default; 
        char m_name[16];
    };

    template <size_t Size>
    class ParameterList {

        public:
        ParameterList(Parameter ** parameters, size_t length);
        Parameter *getParameter(uint16_t id);
        Parameter *getParameter(const char* name);

        

        private:
        std::array<Parameter*, Size> m_parameters = {nullptr};       
        size_t m_length;
    };

}