#include "systems/Spawner.hpp"
#include "SceneManager.hpp"

namespace ecs {
    void SpawnerSystem::update(SceneManager &sceneManager) {
        ecs::Scene &scene = sceneManager.getCurrentScene();

        for (auto &event : scene.events.at(EventType::Spawn)) {}
    }
}
