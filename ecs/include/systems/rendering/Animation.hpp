#ifndef ANIMATION_SYSTEM_HPP
#define ANIMATION_SYSTEM_HPP

#include <vector>
#include "raylib.h"
#include "components/Animation.hpp"
#include "components/Sprite.hpp"
#include "systems/ISystem.hpp"

namespace ecs {
    class SceneManager;

    class AnimationSystem : public ISystem {
        public:
            void update(SceneManager &sceneManager) override;
    };
}

#endif /* ANIMATION_SYSTEM_HPP */
