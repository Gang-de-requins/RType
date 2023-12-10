#ifndef ANIMATION_SPRITE_SYSTEM_HPP
#define ANIMATION_SPRITE_SYSTEM_HPP

#include "components/Animation.hpp"
#include "components/Sprite.hpp"
#include "Archetype.hpp"
#include "System.hpp"

namespace ecs {
    class RenderAnimationSystem : public System {
        public:
            void update(World &world) override;
    };
}

#endif /* ANIMATION_SPRITE_SYSTEM_HPP */
