#include "systems/Input.hpp"
#include "SceneManager.hpp"

namespace ecs {
    void InputSystem::update(SceneManager &sceneManager) {
        int key = GetKeyPressed();

        if (key != KEY_NULL) {
            sceneManager.emit(sceneManager.getCurrentScene(), DefaultEventType::KeyboardInput, static_cast<DefaultEvent>(key));
        } else {
            Scene &scene = sceneManager.getCurrentScene();

            scene.events.at(DefaultEventType::KeyboardInput).clear();
        }
    }
}
