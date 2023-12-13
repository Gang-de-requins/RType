#ifndef SPRITE_COMPONENT_HPP
#define SPRITE_COMPONENT_HPP

#include <string_view>
#include "Rectangle.hpp"
#include "Vector2.hpp"

namespace ecs {
    struct Sprite {
        std::string_view path;
        Rectangle source;
        Vector2 origin;
    };
}

#endif /* SPRITE_COMPONENT_HPP */
