/*
** EPITECH PROJECT, 2024
** RType
** File description:
** Controllable
*/

#include <vector>
#include <algorithm>
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Acceleration.hpp"
#include "Entity.hpp"
#include "systems/ISystem.hpp"
#include "GameEvents.hpp"

namespace ecs
{
	class MovementSystem : public ISystem {
		public:
			void update(SceneManager& sceneManager) override;

		private:
			void move(SceneManager &sceneManager, Entity *entity);
	};
}