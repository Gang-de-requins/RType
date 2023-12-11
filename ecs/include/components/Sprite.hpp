#ifndef SPRITE_COMPONENT_HPP
#define SPRITE_COMPONENT_HPP

#include "raylib.h"

namespace ecs {
    /// @brief Structure representing the sprite data of an entity.
    struct Sprite {
        /// The texture of the sprite.
        Texture2D texture;

        /// The source rectangle defining the portion of the texture to use.
        Rectangle source;

        /// The origin point of the sprite in local coordinates.
        Vector2 origin;
    };
}

#endif /* SPRITE_COMPONENT_HPP */
