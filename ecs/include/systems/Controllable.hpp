#ifndef CONTROLABLE_SYSTEM_HPP
#define CONTROLABLE_SYSTEM_HPP

#include <vector>
#include "raylib.h"
#include "components/Acceleration.hpp"
#include "components/Controllable.hpp"
#include "components/Sound.hpp"
#include "ISystem.hpp"

namespace ecs {
    class SceneManager;

    class ControllableSystem : public ISystem {
        public:
            void update(SceneManager &sceneManager) override;
    };
}

#endif /* CONTROLABLE_SYSTEM_HPP */
