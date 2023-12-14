#ifndef TEXT_SYSTEM_HPP
#define TEXT_SYSTEM_HPP

#include <vector>
#include "raylib.h"
#include "components/Position.hpp"
#include "components/Text.hpp"
#include "components/Color.hpp"
#include "components/FontSize.hpp"
#include "systems/ISystem.hpp"

namespace ecs {
    class SceneManager;

    class TextSystem : public ISystem {
        public:
            void update(SceneManager &sceneManager) override;
    };
}

#endif /* TEXT_SYSTEM_HPP */
