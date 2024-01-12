#ifndef COLLISION_COMPONENT_HPP
#define COLLISION_COMPONENT_HPP

#include <vector>

namespace ecs {

    /**
     * @struct Collision
     * @brief Collision component
     * 
     * @details
     * This component is used to handle collision properties of an entity. It includes information about whether the entity is currently colliding with something, what entities it's colliding with, and whether it's overlapping with another entity.
     * 
     * @var Collision::isColliding
     * A boolean value indicating whether the entity is currently in a collision state.
     * 
     * @var Collision::collidingWith
     * A vector of entity IDs that the entity is currently colliding with.
     * 
     * @var Collision::isOverlap
     * A boolean value indicating whether the entity's collision is considered as an overlap with another entity.
     */
    struct Collision {
        bool isColliding;
        std::vector<std::size_t> collidingWith;
        bool isOverlap;
    };
}

#endif /* COLLISION_COMPONENT_HPP */
