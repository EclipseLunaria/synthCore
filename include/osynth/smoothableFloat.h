#pragma once
#include "utils.h"

namespace OSynthCore {

    const float DEFAULT_SMOOTHING_FACTOR = 15.0;

    class SmoothableFloat {
        private:
        float m_current_value;
        float m_target_value;
        float m_smoothing_factor;

        const float m_smoothing_threshold = OSynthUtils::decibelToLinear(-18.0);

        public:
        SmoothableFloat(float f, float smoothing_factor = DEFAULT_SMOOTHING_FACTOR);

        void set(const float f);

        float get_target() const;
        float get_current() const;

        void set_smoothing_factor(const float ms);
        float get_smoothing_factor() const;

        float next(int sample_rate);

        SmoothableFloat & operator=(const float other);
        private:
        bool is_smoothing();
    };

}