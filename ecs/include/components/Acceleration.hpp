#ifndef ACCELERATION_COMPONENT_HPP
#define ACCELERATION_COMPONENT_HPP

#include "raylib.h"

namespace ecs {
    /// @brief Structure representing the acceleration data of an entity.
    struct Acceleration {
        /// x component of the acceleration.
        float x;

        /// y component of the acceleration.
        float y;

        /// The maximum allowed speed.
        float maxSpeed;
    };
}

#endif /* ACCELERATION_COMPONENT_HPP */

