#ifndef VELOCITY_COMPONENT_HPP
#define VELOCITY_COMPONENT_HPP

namespace ecs {
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
