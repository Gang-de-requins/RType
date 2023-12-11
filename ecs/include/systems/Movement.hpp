#ifndef MOVEMENT_SYSTEM_HPP
#define MOVEMENT_SYSTEM_HPP

#include <memory>
#include <vector>
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Acceleration.hpp"
#include "Archetype.hpp"
#include "System.hpp"

namespace ecs {
    class MovementSystem : public System {
        public:
            void update(World &world) override;
    };
}


#endif /* MOVEMENT_SYSTEM_HPP */