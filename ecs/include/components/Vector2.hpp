#ifndef VECTOR2_COMPONENT_HPP
#define VECTOR2_COMPONENT_HPP

namespace ecs {

    /**
     * @struct Vector2
     * @brief Vector2 component
     * 
     * @details
     * This component represents a 2D vector and is used for various purposes such as defining positions, velocities, and sizes in a 2D space. It contains two float values representing the x and y components of the vector.
     * 
     * @var Vector2::x
     * The x-component of the vector.
     * 
     * @var Vector2::y
     * The y-component of the vector.
     */
    struct Vector2 {
        float x;
        float y;
    };
}

#endif /* VECTOR2_COMPONENT_HPP */
