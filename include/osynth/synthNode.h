#pragma once

namespace OSynth::Core {
    class SynthNode {
        SynthNode * m_parent = nullptr;

        public:
        SynthNode(SynthNode * parent = nullptr);
        SynthNode * getParent();
        int getSampleRate();
        
    };
}