#include "systems/rendering/Render.hpp"

namespace ecs {
    RenderSystem::RenderSystem()
    {
        this->m_systems.push_back(std::make_shared<AnimationSystem>());
        this->m_systems.push_back(std::make_shared<NameSystem>());
        this->m_systems.push_back(std::make_shared<SpriteSystem>());
        this->m_systems.push_back(std::make_shared<RectangleSystem>());
        this->m_systems.push_back(std::make_shared<TextSystem>());
        this->m_systems.push_back(std::make_shared<TextInputSystem>());
    }

    void RenderSystem::update(SceneManager &sceneManager)
    {
        for (auto &system : this->m_systems)
            system->update(sceneManager);
    }
}
