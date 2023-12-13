#ifndef ANIMATION_COMPONENT_HPP
#define ANIMATION_COMPONENT_HPP

#include <chrono>
#include "Rectangle.hpp"

namespace ecs {
    struct Animation {
        Rectangle offset;
        int frames;
        int currentFrame;
        int frameTime;
        std::chrono::steady_clock::time_point lastUpdate;
    };
}

#endif /* ANIMATION_COMPONENT_HPP */
