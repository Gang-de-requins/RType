#ifndef SPRITE_SYSTEM_HPP
#define SPRITE_SYSTEM_HPP

#include <memory>
#include <vector>
#include "raylib.h"
#include "components/Position.hpp"
#include "components/Sprite.hpp"
#include "components/Scale.hpp"
#include "components/Rect.hpp"
#include "Archetype.hpp"
#include "System.hpp"

namespace ecs {
    class RenderSpriteSystem : public System {
        public:
            void update(World &world) override;
    };
}

#endif /* SPRITE_SYSTEM_HPP */
