#include "systems/Destruction.hpp"
#include "SceneManager.hpp"

namespace ecs {
    void DestructionSystem::update(SceneManager &sceneManager) {
        ecs::Scene &scene = sceneManager.getCurrentScene();

        for (auto &event : scene.events.at(EventType::Destroy)) {
            for (auto &entity : event.entities) {
                sceneManager.destroyEntity(scene, *entity);
            }
        }
        scene.events.at(EventType::Destroy).clear();
    }
}
