#ifndef SPRITE_COMPONENT_HPP
#define SPRITE_COMPONENT_HPP

#include <string>
#include "Rectangle.hpp"
#include "Vector2.hpp"

namespace ecs {

    /**
     * @struct Sprite
     * @brief Sprite component
     * 
     * @details
     * This component is used to represent a graphical sprite in the game or application. It includes the path to the sprite's image file, a rectangle to specify a particular region of the sprite sheet (if applicable), and the sprite's origin for positioning and transformations.
     * 
     * @var Sprite::path
     * The file path to the sprite image. This path is used to load the image for rendering the sprite.
     * 
     * @var Sprite::source
     * A Rectangle structure defining a specific region of the sprite sheet. This is useful for sprites that are part of a larger image or sprite sheet.
     * 
     * @var Sprite::origin
     * A Vector2 structure representing the origin point of the sprite. This point is used as the reference for positioning and transforming the sprite.
     */
    struct Sprite {
        std::string path;
        Rectangle source;
        Vector2 origin;
    };
}

#endif /* SPRITE_COMPONENT_HPP */
