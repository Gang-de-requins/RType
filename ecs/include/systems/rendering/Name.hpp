#ifndef NAME_SYSTEM_HPP
#define NAME_SYSTEM_HPP

#include <vector>
#include "raylib.h"
#include "components/Name.hpp"
#include "components/Position.hpp"
#include "systems/ISystem.hpp"

namespace ecs {
    class SceneManager;

    class NameSystem : public ISystem {
        public:
            void update(SceneManager &sceneManager) override;
    };
}

#endif /* NAME_SYSTEM_HPP */
