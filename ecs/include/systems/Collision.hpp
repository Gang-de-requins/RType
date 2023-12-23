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

    /**
     * @struct CollisionInfo
     * @brief Structure to hold collision related information
     * 
     * @details
     * This structure is used to store references to the components of two entities that are being checked for collision. It simplifies the process of passing multiple components between functions.
     * 
     * @var CollisionInfo::sprite1
     * Reference to the sprite component of the first entity.
     * @var CollisionInfo::position1
     * Reference to the position component of the first entity.
     * @var CollisionInfo::scale1
     * Reference to the scale component of the first entity.
     * @var CollisionInfo::rotation1
     * Reference to the rotation component of the first entity.
     * 
     * @var CollisionInfo::sprite2
     * Reference to the sprite component of the second entity.
     * @var CollisionInfo::position2
     * Reference to the position component of the second entity.
     * @var CollisionInfo::scale2
     * Reference to the scale component of the second entity.
     * @var CollisionInfo::rotation2
     * Reference to the rotation component of the second entity.
     */
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

    /**
     * @class CollisionSystem
     * @brief Collision System class
     * 
     * @details
     * Part of the Entity Component System, this class is responsible for handling collision detection and responses for entities. It utilizes various components such as Collision, Position, Sprite, and others to determine and manage collisions.
     * 
     */
    class CollisionSystem : public ISystem {
    public:
        /**
         * @brief Updates the state of entity collisions
         * 
         * @param sceneManager Reference to the SceneManager which manages the current scene and its entities.
         * 
         */
        void update(SceneManager &sceneManager) override;

    private:
        /**
         * @brief Checks if two entities are colliding
         * 
         * @param collisionInfo A CollisionInfo structure containing references to the components of the two entities being checked for collision.
         * 
         * @return bool True if there is a collision between the two entities, false otherwise.
         * 
         */
        bool isColliding(const CollisionInfo &collisionInfo);
    };
}

#endif /* COLLISION_SYSTEM_HPP */
