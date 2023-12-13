#ifndef ACCELERATION_COMPONENT_HPP
#define ACCELERATION_COMPONENT_HPP

namespace ecs {
    struct Acceleration {
        float ddx;
        float ddy;
        float maxSpeed;
    };
}

#endif /* ACCELERATION_COMPONENT_HPP */
