#include "Game.hpp"

namespace rtype {
    void Game::loadMenu(ecs::Scene &scene) {
        this->m_world.registerSystems<
            ecs::MusicSystem,
            ecs::ControllableSystem,
            ecs::MovementSystem,
            ecs::CollisionSystem,
            ecs::LifeSystem,
            ecs::ParallaxSystem,
            ecs::RenderSystem,
            ecs::ClickableSystem
        >(scene);

        std::cout << "In Menu" << std::endl;

        ecs::Entity &Bakckground = this->m_world.createEntity(scene);
        this->m_world.assign(Bakckground, ecs::Position{0, 0});
        this->m_world.assign(Bakckground, ecs::Sprite{"assets/Menu/Space-Back-Menu.png", ecs::Rectangle{0, 0, 1920, 1080}, ecs::Vector2{0, 0}});
        this->m_world.assign(Bakckground, ecs::Scale{1, 1});
        this->m_world.assign(Bakckground, ecs::Rotation{0});

        ecs::Entity &Title = this->m_world.createEntity(scene);
        this->m_world.assign(Title, ecs::Position{350, 5});
        this->m_world.assign(Title, ecs::Sprite{"assets/Menu/r-type.png", ecs::Rectangle{0, 0, 1258, 481}, ecs::Vector2{0, 0}});
        this->m_world.assign(Title, ecs::Scale{1, 1});
        this->m_world.assign(Title, ecs::Rotation{0});

        ecs::Entity &ButtonConnect = this->m_world.createEntity(scene);
        this->m_world.assign(ButtonConnect, ecs::Position{810, 300});
        this->m_world.assign(ButtonConnect, ecs::Sprite{"assets/Menu/buttonPlay.png", ecs::Rectangle{0, 0, 300, 153}, ecs::Vector2{0, 0}});
        this->m_world.assign(ButtonConnect, ecs::Scale{1, 1});
        this->m_world.assign(ButtonConnect, ecs::Rotation{0});
        this->m_world.assign(ButtonConnect, ecs::Clickable{false, [this](ecs::Clickable&) {
            std::cout << "ButtonPlay clicked" << std::endl;
            this->m_network.connect(this->m_network.m_ip, this->m_network.m_port, *this);
            this->m_world.switchToScene(2);
        }});

        ecs::Entity &ButtonSettings = this->m_world.createEntity(scene);
        this->m_world.assign(ButtonSettings, ecs::Position{810, 460});
        this->m_world.assign(ButtonSettings, ecs::Sprite{"assets/Menu/buttonSettings.png", ecs::Rectangle{0, 0, 300, 153}, ecs::Vector2{0, 0}});
        this->m_world.assign(ButtonSettings, ecs::Scale{1, 1});
        this->m_world.assign(ButtonSettings, ecs::Rotation{0});
        this->m_world.assign(ButtonSettings, ecs::Clickable{false, [this](ecs::Clickable&) {this->m_world.switchToScene(1);}});
    }
}
