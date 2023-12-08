#ifndef SPRITE_COMPONENT_HPP
#define SPRITE_COMPONENT_HPP

#include "raylib.h"

namespace ecs {
    struct Sprite {
        Texture2D texture;
        Rectangle source;
        Vector2 origin;
    };
}

#endif /* SPRITE_COMPONENT_HPP */
