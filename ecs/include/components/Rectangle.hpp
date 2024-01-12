#ifndef RECTANGLE_COMPONENT_HPP
#define RECTANGLE_COMPONENT_HPP

namespace ecs {

    /**
     * @struct Rectangle
     * @brief Rectangle component
     * 
     * @details
     * This component is used to define a rectangular shape. It is useful for graphical representations, collision detection, and other spatial computations. The rectangle is defined by its position (x, y) and dimensions (width, height).
     * 
     * @var Rectangle::x
     * The x-coordinate of the top-left corner of the rectangle.
     * 
     * @var Rectangle::y
     * The y-coordinate of the top-left corner of the rectangle.
     * 
     * @var Rectangle::width
     * The width of the rectangle.
     * 
     * @var Rectangle::height
     * The height of the rectangle.
     */
    struct Rectangle {
        float x;
        float y;
        float width;
        float height;
    };
}

#endif /* RECTANGLE_COMPONENT_HPP */
