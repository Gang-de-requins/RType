#ifndef MOVEMENT_SYSTEM_HPP
#define MOVEMENT_SYSTEM_HPP

#include <vector>
#include <algorithm>
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Acceleration.hpp"
#include "Entity.hpp"
#include "systems/ISystem.hpp"

namespace ecs {
	class MovementSystem : public ISystem {
		public:
			void update(SceneManager& sceneManager) override;

		private:
			void move(SceneManager &sceneManager, Entity *entity);
	};
}

#endif /* MOVEMENT_SYSTEM_HPP */
