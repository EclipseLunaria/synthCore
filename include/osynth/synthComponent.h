#pragma once
#include <concepts>
#include "osynth/config.h"
namespace OSynth::Core{
    template <class Derived>
    class SynthComponent{
        
        public:
        SynthComponent(){

        }
        SynthComponent(SynthComponent * parent){
            m_parent = parent;
        }

        void initialize() {
            derived().initializeImpl();
        }

        void reset() {
            derived().resetImpl();
        }
        SynthComponent * getParent(){
            return m_parent;
        }
        int getSampleRate() {
            auto parent = getParent();
            return parent ? parent->getSampleRate() : Config::get_global_sample_rate();
        }


        private:
        SynthComponent * m_parent = nullptr;
        friend Derived;
        Derived& derived() {
            return static_cast<Derived&>(*this);
        }

    };
}