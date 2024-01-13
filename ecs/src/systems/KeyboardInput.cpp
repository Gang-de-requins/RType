#include "systems/KeyboardInput.hpp"
#include "SceneManager.hpp"

namespace ecs {
	void KeyboardInputSystem::update(SceneManager& sceneManager) {
		// int key = GetKeyPressed();

		// if (key != KEY_NULL) {
		// 	sceneManager.emit(sceneManager.getCurrentScene(), EventType::KeyboardInput, key);
		// } else {
		// 	sceneManager.getCurrentScene().events.at(EventType::KeyboardInput).clear();
		// }

		static_cast<void>(sceneManager);
	}
}
