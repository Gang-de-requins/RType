#ifndef SPRITE_SYSTEM_HPP
#define SPRITE_SYSTEM_HPP

#include <vector>
#include "raylib.h"
#include "components/Position.hpp"
#include "components/Sprite.hpp"
#include "components/Scale.hpp"
#include "components/Rotation.hpp"
#include "systems/ISystem.hpp"

namespace ecs {
    class World;

    class SpriteSystem : public ISystem {
        public:
            void update(World &world) override;
    };
}

#endif /* SPRITE_SYSTEM_HPP */
