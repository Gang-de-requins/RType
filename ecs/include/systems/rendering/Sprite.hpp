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
    class SceneManager;

    class SpriteSystem : public ISystem {
        public:
            void update(SceneManager &sceneManager) override;
    };
}

#endif /* SPRITE_SYSTEM_HPP */
