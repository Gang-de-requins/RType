#ifndef CLICKABLE_SYSTEM_HPP_
#define CLICKABLE_SYSTEM_HPP_

    #include <vector>
    #include <algorithm>
    #include "raylib.h"
    #include "components/Clickable.hpp"
    #include "ISystem.hpp"
    #include "Entity.hpp"

namespace ecs {
    class SceneManager;

    class ClickableSystem : public ISystem {

        public:

            void update(SceneManager &sceneManager) override;

        private:

            bool mouseInSprite(::Vector2 mousePosition, Entity &entitie, SceneManager &sceneManager);
    };
}

#endif /* !CLICKABLE_HPP_ */
