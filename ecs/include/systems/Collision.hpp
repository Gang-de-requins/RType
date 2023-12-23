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

    struct CollisionInfo {
        Sprite &sprite1;
        Position &position1;
        Scale &scale1;
        Rotation &rotation1;

        Sprite &sprite2;
        Position &position2;
        Scale &scale2;
        Rotation &rotation2;
    };

    class CollisionSystem : public ISystem {
        public:
            void update(SceneManager &sceneManager) override;
        
        private:
            bool isColliding(const CollisionInfo &collisionInfo);
    };
}

#endif /* COLLISION_SYSTEM_HPP */
