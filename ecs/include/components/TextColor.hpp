#ifndef TEXT_COLOR_COMPONENT_HPP
#define TEXT_COLOR_COMPONENT_HPP

namespace ecs {
    
        /**
        * @struct TextColor
        * @brief Text color component
        * 
        * @details
        * This component is used to store color information of an entity. It consists of four components: red, green, blue, and alpha (transparency).
        * 
        * @var TextColor::r
        * The red component of the color, represented as an unsigned char.
        * 
        * @var TextColor::g
        * The green component of the color, represented as an unsigned char.
        * 
        * @var TextColor::b
        * The blue component of the color, represented as an unsigned char.
        * 
        * @var TextColor::a
        * The alpha (transparency) component of the color, represented as an unsigned char.
        */
        struct TextColor {
            unsigned char r;
            unsigned char g;
            unsigned char b;
            unsigned char a;
        };
}

#endif /* TEXT_COLOR_COMPONENT_HPP */
