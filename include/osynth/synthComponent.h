#pragma once
#include <concepts>
#include "osynth/config.h"
namespace OSynth::Core{
    template <class Derived>
    class SynthComponent{
        
        public:
        SynthComponent(){

        }
        void initialize() {
            derived().initializeImpl();
        }

        void reset() {
            derived().resetImpl();
        }

        void update() {
            derived().updateImpl();
        }
        private:
        friend Derived;
        Derived& derived() {
            return static_cast<Derived&>(*this);
        }

    };
}