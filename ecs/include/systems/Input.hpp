#ifndef INPUT_SYSTEM_HPP
#define INPUT_SYSTEM_HPP

#include <vector>
#include <algorithm>
#include "raylib.h"
#include "ISystem.hpp"

namespace ecs {
    class InputSystem : public ISystem {
        public:
            void update(SceneManager &sceneManager) override;
    };
}

#endif /* INPUT_SYSTEM_HPP */
