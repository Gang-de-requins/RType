#include "systems/Input.hpp"
#include "SceneManager.hpp"

namespace ecs {
    void InputSystem::update(SceneManager &sceneManager) {
        int key = GetKeyPressed();

        if (key != KEY_NULL) {
            sceneManager.emit(sceneManager.getCurrentScene(), EventType::KeyboardInput, static_cast<Event>(key));
        } else {
            Scene &scene = sceneManager.getCurrentScene();

            scene.events.at(EventType::KeyboardInput).clear();
        }
    }
}
