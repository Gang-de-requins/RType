#ifndef SPAWNER_SYSTEM_HPP
#define SPAWNER_SYSTEM_HPP

#include <vector>
#include <algorithm>
#include "raylib.h"
#include "components/Components.hpp"
#include "systems/ISystem.hpp"
#include "Entity.hpp"
#include "Scene.hpp"
#include "GameEvents.hpp"

namespace ecs {
    class SpawnerSystem : public ISystem {
    public:
        void update(SceneManager& sceneManager) override;

    private:
        void spawnBullet(SceneManager& sceneManager, Entity& entity, Scene& scene, bool isPlayer);
    };
}

#endif /* SPAWNER_SYSTEM_HPP */
