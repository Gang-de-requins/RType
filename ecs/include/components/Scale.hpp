#ifndef SCALE_COMPONENT_HPP
#define SCALE_COMPONENT_HPP

namespace ecs {
    struct Scale {
        float x;
        float y;

        Scale operator+(const Scale& other) const {
            return { x + other.x, y + other.y };
        }

        Scale &operator+=(const Scale& other) {
            x += other.x;
            y += other.y;
            return *this;
        }

        Scale operator-(const Scale& other) const {
            return { x - other.x, y - other.y };
        }

        Scale &operator-=(const Scale& other) {
            x -= other.x;
            y -= other.y;
            return *this;
        }
    };
}

#endif /* SCALE_COMPONENT_HPP */
