/*
** EPITECH PROJECT, 2024
** RType
** File description:
** Controllable
*/

#ifndef CONTROLLABLE_SYSTEM_HPP
#define CONTROLLABLE_SYSTEM_HPP

#include <vector>
#include "raylib.h"
#include "components/Acceleration.hpp"
#include "components/Controllable.hpp"
#include "components/Sound.hpp"
#include "systems/ISystem.hpp"
#include "Scene.hpp"
#include "Events.hpp"

namespace ecs
{
	class ControllableSystem : public ISystem {
		public:
			void update(SceneManager& sceneManager) override;
	};
}

#endif /* CONTROLLABLE_SYSTEM_HPP */