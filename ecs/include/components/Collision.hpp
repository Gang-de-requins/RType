#ifndef COLLISION_COMPONENT_HPP
#define COLLISION_COMPONENT_HPP

#include <vector>

namespace ecs {
    struct Collision {
        bool isColliding;
        std::vector<std::size_t> collidingWith;
    };
}

#endif /* COLLISION_COMPONENT_HPP */
