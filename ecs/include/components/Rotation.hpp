#ifndef ROTATION_COMPONENT_HPP
#define ROTATION_COMPONENT_HPP

namespace ecs {
    struct Rotation {
        float angle;

        Rotation operator+(const Rotation& other) const {
            return { angle + other.angle };
        }

        Rotation &operator+=(const Rotation& other) {
            angle += other.angle;
            return *this;
        }

        Rotation operator-(const Rotation& other) const {
            return { angle - other.angle };
        }

        Rotation &operator-=(const Rotation& other) {
            angle -= other.angle;
            return *this;
        }
    };
}

#endif /* ROTATION_COMPONENT_HPP */
