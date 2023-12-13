#ifndef ANIMATION_SYSTEM_HPP
#define ANIMATION_SYSTEM_HPP

#include <vector>
#include "raylib.h"
#include "components/Animation.hpp"
#include "components/Sprite.hpp"
#include "systems/ISystem.hpp"

namespace ecs {
    class World;

    class AnimationSystem : public ISystem {
        public:
            void update(World &world) override;
    };
}

#endif /* ANIMATION_SYSTEM_HPP */
