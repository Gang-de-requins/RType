/*
** EPITECH PROJECT, 2024
** RType
** File description:
** Controllable
*/

#include "systems/Controllable.hpp"
#include "SceneManager.hpp"

namespace ecs
{

    void ControllableSystem::update(SceneManager& sceneManager)
    {
		Scene &scene = sceneManager.getCurrentScene();
		auto entities = sceneManager.view<Controllable>(scene);

		for (auto &entity : entities) {
			Controllable &controllable = sceneManager.get<Controllable>(*entity);
			bool actionFound = false;

			for (auto &action : controllable.actions) {
				switch (std::get<0>(action.second)) {
					case ActionTrigger::Hold:
						if (IsKeyDown(action.first)) {
							actionFound = true;
							std::get<1>(action.second)(sceneManager, scene, entity);
						}
						break;
					case ActionTrigger::Press:
						if (IsKeyPressed(action.first)) {
							actionFound = true;
							std::get<1>(action.second)(sceneManager, scene, entity);
						}
						break;
					default:
						break;
				}
			}
			if (!actionFound) {
				scene.events[EventType::Input].push_back({
					GameEvent::StopMoving,
					{entity}
				});
			}
		}
    }
}
