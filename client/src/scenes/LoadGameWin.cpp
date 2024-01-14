#include "Game.hpp"

namespace rtype {
    void Game::loadWin(ecs::Scene &scene)
    {
        this->m_world.registerSystems<
            ecs::RenderSystem,
            ecs::ClickableSystem
        >(scene);

        std::cout << "In Win" << std::endl;

        ecs::Entity &spaceBg = this->m_world.createEntity(scene);
        this->m_world.assign(spaceBg, ecs::Position{0, 0});
        this->m_world.assign(spaceBg, ecs::Sprite{"assets/Menu/Space-Back-Menu.png", ecs::Rectangle{0, 0, 1920, 1080}, ecs::Vector2{0, 0}});
        this->m_world.assign(spaceBg, ecs::Scale{1, 1});
        this->m_world.assign(spaceBg, ecs::Rotation{0});

        ecs::Entity &text = this->m_world.createEntity(scene);
        this->m_world.assign(text, ecs::Position{1920 / 2 - 200, 1080 / 2 - 100});
        this->m_world.assign(text, ecs::Text{"You win !"});
        this->m_world.assign(text, ecs::FontSize{100});
        this->m_world.assign(text, ecs::TextColor{255, 255, 255, 255});
        this->m_world.assign(text, ecs::Rotation{0});
    }
}
