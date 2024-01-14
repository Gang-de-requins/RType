/*
** EPITECH PROJECT, 2024
** RType
** File description:
** Collision
*/

#ifndef COLLISION_SYSTEM_HPP
#define COLLISION_SYSTEM_HPP

#include <vector>
#include <algorithm>
#include "components/Collision.hpp"
#include "components/Position.hpp"
#include "components/Sprite.hpp"
#include "components/Rectangle.hpp"
#include "components/Velocity.hpp"
#include "components/Acceleration.hpp"
#include "components/Scale.hpp"
#include "components/Rotation.hpp"
#include "components/Health.hpp"
#include "components/Damage.hpp"
#include "Entity.hpp"
#include "Scene.hpp"
#include "systems/ISystem.hpp"

namespace ecs
{
    struct CollisionInfo {
        Sprite &sprite;
        Position &position;
        Scale &scale;
        Rotation &rotation;
    };


	class CollisionSystem : public ISystem {
		public:
			void update(SceneManager& sceneManager) override;

		private:
            bool isColliding(const CollisionInfo &collisionInfo1, const CollisionInfo &collisionInfo2);

	};
}

#endif /* COLLISION_SYSTEM_HPP */