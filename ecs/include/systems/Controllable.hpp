#ifndef CONTROLABLE_SYSTEM_HPP
#define CONTROLABLE_SYSTEM_HPP

#include <vector>
#include "raylib.h"
#include "components/Acceleration.hpp"
#include "components/Controllable.hpp"
#include "ISystem.hpp"

namespace ecs {
    class World;

    class ControllableSystem : public ISystem {
        public:
            void update(World &world) override;
    };
}

#endif /* CONTROLABLE_SYSTEM_HPP */
