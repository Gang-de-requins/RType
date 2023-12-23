#ifndef VELOCITY_COMPONENT_HPP
#define VELOCITY_COMPONENT_HPP

namespace ecs {

    /**
     * @struct Velocity
     * @brief Velocity component
     * 
     * @details
     * This component is used to store and manage the velocity of an entity in a 2D space. It contains two float values representing the velocity components along the x and y axes. The component includes operators for manipulating the velocity.
     * 
     * @var Velocity::dx
     * The velocity component along the x-axis.
     * 
     * @var Velocity::dy
     * The velocity component along the y-axis.
     * 
     * The operators (+, +=, -, -=) are defined to facilitate the addition and subtraction of velocity values, enabling easy modifications to an entity's velocity.
     */
    struct Velocity {
        float dx;
        float dy;

        Velocity operator+(const Velocity& other) const {
            return { dx + other.dx, dy + other.dy };
        }

        Velocity &operator+=(const Velocity& other) {
            dx += other.dx;
            dy += other.dy;
            return *this;
        }

        Velocity operator-(const Velocity& other) const {
            return { dx - other.dx, dy - other.dy };
        }

        Velocity &operator-=(const Velocity& other) {
            dx -= other.dx;
            dy -= other.dy;
            return *this;
        }
    };
}

#endif /* VELOCITY_COMPONENT_HPP */
