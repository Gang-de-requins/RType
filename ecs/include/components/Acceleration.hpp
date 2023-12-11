#ifndef ACCELERATION_COMPONENT_HPP
#define ACCELERATION_COMPONENT_HPP

#include "raylib.h"

namespace ecs {
    struct Acceleration {
        float x;
        float y;
        float maxSpeed;
    };
}

#endif /* ACCELERATION_COMPONENT_HPP */
