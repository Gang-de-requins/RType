#ifndef ACCELERATION_COMPONENT_HPP
#define ACCELERATION_COMPONENT_HPP

namespace ecs {
    /**
     * @struct Acceleration
     * @brief Acceleration component
     * 
     * @details
     * This component is used to store the acceleration of an entity.
     * 
     * @var Acceleration::ddx
     * The acceleration on the x axis.
     * 
     * @var Acceleration::ddy
     * The acceleration on the y axis.
     * 
     * @var Acceleration::maxSpeed
     * The maximum speed of the entity.
    */
    struct Acceleration {
        float ddx;
        float ddy;
        float maxSpeed;
    };
}

#endif /* ACCELERATION_COMPONENT_HPP */
