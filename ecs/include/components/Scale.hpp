#ifndef SCALE_COMPONENT_HPP
#define SCALE_COMPONENT_HPP

namespace ecs {

    /**
     * @struct Scale
     * @brief Scale component
     * 
     * @details
     * This component is used to store and manage the scale of an entity in a 2D space. It holds scaling factors for the x and y axes, allowing for non-uniform scaling. The component includes operators for manipulating the scale.
     * 
     * @var Scale::x
     * The scaling factor along the x-axis.
     * 
     * @var Scale::y
     * The scaling factor along the y-axis.
     * 
     * The operators (+, +=, -, -=) are defined to facilitate the addition and subtraction of scale values, enabling easy modifications to an entity's scale.
     */
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
