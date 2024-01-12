#ifndef ROTATION_COMPONENT_HPP
#define ROTATION_COMPONENT_HPP

namespace ecs {

    /**
     * @struct Rotation
     * @brief Rotation component
     * 
     * @details
     * This component is used to store and manage the rotational aspect of an entity. It holds the rotation angle and includes operators for manipulating the rotation.
     * 
     * @var Rotation::angle
     * The rotation angle of the entity, typically in degrees or radians.
     * 
     * The operators (+, +=, -, -=) are defined to facilitate the addition and subtraction of rotation angles, allowing for straightforward modifications to an entity's rotation.
     */
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
