#include "systems/Controllable.hpp"
#include "SceneManager.hpp"

namespace ecs {
	void ControllableSystem::update(SceneManager& sceneManager) {
		Scene &scene = sceneManager.getCurrentScene();

		if (IsKeyDown(KEY_UP)) {
			this->addMoveEvent(sceneManager, scene, GameEvent::MoveUp);
		} else if (IsKeyDown(KEY_DOWN)) {
			this->addMoveEvent(sceneManager, scene, GameEvent::MoveDown);
		} else if (IsKeyDown(KEY_LEFT)) {
			this->addMoveEvent(sceneManager, scene, GameEvent::MoveLeft);
		} else if (IsKeyDown(KEY_RIGHT)) {
			this->addMoveEvent(sceneManager, scene, GameEvent::MoveRight);
		} else if (IsKeyPressed(KEY_SPACE)) {
			this->addShootEvent(sceneManager, scene, GameEvent::SpawnPlayerBullet);
		} else {
			this->addMoveEvent(sceneManager, scene, GameEvent::StopMoving);
		}
	}

	void ControllableSystem::addMoveEvent(SceneManager& sceneManager, Scene& scene, int event) {
		auto entities = sceneManager.view<Controllable>(scene);

		for (auto &entity : entities) {
			scene.events[EventType::Input].push_back({
				event,
				{entity}
			});
		}
	}

	void ControllableSystem::addShootEvent(SceneManager& sceneManager, Scene& scene, int event) {
		auto entities = sceneManager.view<Controllable>(scene);

		for (auto &entity : entities) {
			Controllable &controllable = sceneManager.get<Controllable>(*entity);

			if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - controllable.shootUpdate).count() >= controllable.timeOut) {
				controllable.shootUpdate = std::chrono::steady_clock::now();
				scene.events[EventType::Spawn].push_back({
					event,
					{entity}
				});
			}
		}
	}
}
