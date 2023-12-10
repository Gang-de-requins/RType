#ifndef ANIMATION_COMPONENT_HPP
#define ANIMATION_COMPONENT_HPP

// chrono
#include <chrono>
#include "raylib.h"

namespace ecs {
    struct Animation {
        Rectangle offset;
        int frames;
        int currentFrame;
        std::chrono::steady_clock::time_point chrono;
        int elapsedTime; // in milliseconds
    };
}

#endif /* ANIMATION_COMPONENT_HPP */
