#ifndef SPAWNER_SYSTEM_HPP
#define SPAWNER_SYSTEM_HPP

#include <vector>
#include <algorithm>
#include "raylib.h"
#include "components/Components.hpp"
#include "ISystem.hpp"
#include "Entity.hpp"

namespace ecs {
    class SpawnerSystem : public ISystem {
        public:
            void update(SceneManager &sceneManager) override;
    };
}

#endif /* SPAWNER_SYSTEM_HPP */
