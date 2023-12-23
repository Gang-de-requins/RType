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

        Acceleration operator+(const Acceleration &other) const {
            return { ddx + other.ddx, ddy + other.ddy, maxSpeed + other.maxSpeed };
        }

        Acceleration &operator+=(const Acceleration &other) {
            ddx += other.ddx;
            ddy += other.ddy;
            maxSpeed += other.maxSpeed;
            return *this;
        }

        Acceleration operator-(const Acceleration &other) const {
            return { ddx - other.ddx, ddy - other.ddy, maxSpeed - other.maxSpeed };
        };

        Acceleration &operator-=(const Acceleration &other) {
            ddx -= other.ddx;
            ddy -= other.ddy;
            maxSpeed -= other.maxSpeed;
            return *this;
        };
    };
}

#endif /* ACCELERATION_COMPONENT_HPP */
