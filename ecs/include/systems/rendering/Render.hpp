#ifndef RENDER_SYSTEM_HPP
#define RENDER_SYSTEM_HPP

#include "Animation.hpp"
#include "Name.hpp"
#include "Rectangle.hpp"
#include "Sprite.hpp"
#include "Text.hpp"
#include "TextInput.hpp"
#include "../MainSystem.hpp"

namespace ecs {
    class RenderSystem : public MainSystem {
        public:
            RenderSystem();
            void update(SceneManager &sceneManager) override;
    };
}

#endif /* RENDER_SYSTEM_HPP */
