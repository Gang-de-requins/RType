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
#include "ISystem.hpp"

namespace ecs {
    class SceneManager;

    class CollisionSystem : public ISystem {
        public:
            void update(SceneManager &sceneManager) override;
        
        private:
            bool isColliding(const Position &pos1, const Sprite &sprite1, const Position &pos2, const Sprite &sprite2);
    };
}

#endif /* COLLISION_SYSTEM_HPP */
