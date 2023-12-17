#ifndef LIFE_SYSTEM_HPP
#define LIFE_SYSTEM_HPP

#include <vector>
#include <algorithm>
#include "components/Health.hpp"
#include "components/Damage.hpp"
#include "components/Collision.hpp"
#include "ISystem.hpp"

namespace ecs {
    class SceneManager;

    class LifeSystem : public ISystem {
        public:
            void update(SceneManager &sceneManager) override;
    };
}

#endif /* LIFE_SYSTEM_HPP */
