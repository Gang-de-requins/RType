#ifndef DESTRUCTION_SYSTEM_HPP
#define DESTRUCTION_SYSTEM_HPP

#include <vector>
#include <algorithm>
#include "raylib.h"
#include "components/Components.hpp"
#include "ISystem.hpp"
#include "Entity.hpp"

namespace ecs {
    class DestructionSystem : public ISystem {
        public:
            void update(SceneManager &sceneManager) override;
    };
}

#endif /* DESTRUCTION_SYSTEM_HPP */
