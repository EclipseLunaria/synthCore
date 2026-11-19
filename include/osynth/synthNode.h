#pragma once
#include "parameter.h"
namespace OSynth::Core {
    class SynthNode {
        SynthNode * m_parent = nullptr;

        public:
        SynthNode(SynthNode * parent = nullptr);
        /// @brief Gets the parent node of the synth node.
        /// @return parent synth node.
        SynthNode * getParent();
        
        Parameter * getParameter(const char * name);
        //Parameter * getParameter(uint16_t id);
        
        
        /// @brief gets the sample rate for the synth node tree. If the parent node is not defined use global sample rate.
        /// @return 
        int getSampleRate();

        virtual void initialize() {}
        virtual void reset() {}
        virtual void update() {}
        
    };
}