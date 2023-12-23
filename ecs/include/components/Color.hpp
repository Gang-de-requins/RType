#ifndef COLOR_COMPONENT_HPP
#define COLOR_COMPONENT_HPP

namespace ecs {

    /**
     * @struct Color
     * @brief Color component
     * 
     * @details
     * This component is used to store color information of an entity. It consists of four components: red, green, blue, and alpha (transparency).
     * 
     * @var Color::r
     * The red component of the color, represented as an unsigned char.
     * 
     * @var Color::g
     * The green component of the color, represented as an unsigned char.
     * 
     * @var Color::b
     * The blue component of the color, represented as an unsigned char.
     * 
     * @var Color::a
     * The alpha (transparency) component of the color, represented as an unsigned char.
     */
    struct Color {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    };
}

#endif /* COLOR_COMPONENT_HPP */
