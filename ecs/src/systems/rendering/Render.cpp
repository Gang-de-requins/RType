#include "systems/rendering/Render.hpp"

namespace ecs {
    RenderSystem::RenderSystem()
    {
        this->m_systems.push_back(std::make_unique<AnimationSystem>());
        this->m_systems.push_back(std::make_unique<NameSystem>());
        this->m_systems.push_back(std::make_unique<RectangleSystem>());
        this->m_systems.push_back(std::make_unique<SpriteSystem>());
        this->m_systems.push_back(std::make_unique<TextSystem>());
        this->m_systems.push_back(std::make_unique<TextInputSystem>());
    }

    void RenderSystem::update(SceneManager &sceneManager)
    {
        for (auto &system : this->m_systems)
            system->update(sceneManager);
    }
}
