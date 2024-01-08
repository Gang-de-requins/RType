#ifndef CONTROLLABLE_SYSTEM_HPP
#define CONTROLLABLE_SYSTEM_HPP

#include <vector>
#include <algorithm>
#include "raylib.h"
#include "components/Controllable.hpp"
#include "systems/ISystem.hpp"

namespace ecs {
    class ControllableSystemCustom : public ISystem {
        public:
            void update(SceneManager &sceneManager) override;
    };
}

#endif /* CONTROLLABLE_SYSTEM_HPP */
