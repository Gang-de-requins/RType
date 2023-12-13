#ifndef MOVEMENT_SYSTEM_HPP
#define MOVEMENT_SYSTEM_HPP

#include <vector>
#include <algorithm>
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Acceleration.hpp"
#include "ISystem.hpp"

namespace ecs {
    class World;

    class MovementSystem : public ISystem {
        public:
            void update(World &world) override;
    };
}


#endif /* MOVEMENT_SYSTEM_HPP */