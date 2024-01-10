#ifndef CONTROLLABLE_SYSTEM_HPP
#define CONTROLLABLE_SYSTEM_HPP

#include <vector>
#include "raylib.h"
#include "components/Acceleration.hpp"
#include "components/Controllable.hpp"
#include "components/Sound.hpp"
#include "systems/ISystem.hpp"
#include "Scene.hpp"
#include "GameEvents.hpp"

namespace ecs {
	class ControllableSystem : public ISystem {
		public:
			void update(SceneManager& sceneManager) override;

		private:
			void addMoveEvent(SceneManager& sceneManager, Scene& scene, int event);
			void addShootEvent(SceneManager& sceneManager, Scene& scene, int event);
	};
}

#endif /* CONTROLLABLE_SYSTEM_HPP */
