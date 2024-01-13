#include "Game.hpp"

namespace rtype {
    void Game::loadChooseRoom(ecs::Scene &scene)
    {
        this->m_world.registerSystems<
            ecs::RenderSystem,
            ecs::ClickableSystem
        >(scene);

        std::cout << "In Choose Room" << std::endl;

        ecs::Entity &Bakckground = this->m_world.createEntity(scene);
        this->m_world.assign(Bakckground, ecs::Position{0, 0});
        this->m_world.assign(Bakckground, ecs::Sprite{"assets/ChooseRoom/Space-Back.png", ecs::Rectangle{0, 0, 1920, 1080}, ecs::Vector2{0, 0}});
        this->m_world.assign(Bakckground, ecs::Scale{1, 1});
        this->m_world.assign(Bakckground, ecs::Rotation{0});

        ecs::Entity &LobbyRoom = this->m_world.createEntity(scene);
        this->m_world.assign(LobbyRoom, ecs::Position{300, 100});
        this->m_world.assign(LobbyRoom, ecs::Rectangle{0, 0, 1320, 780});
        this->m_world.assign(LobbyRoom, ecs::Scale{1, 1});
        this->m_world.assign(LobbyRoom, ecs::Rotation{0});
        this->m_world.assign(LobbyRoom, ecs::Color{200, 200, 200, 150});

        ecs::Entity &TitleRoom1 = this->m_world.createEntity(scene);
        this->m_world.assign(TitleRoom1, ecs::Position{330, 130});
        this->m_world.assign(TitleRoom1, ecs::Rectangle{0, 0, 300, 700});
        this->m_world.assign(TitleRoom1, ecs::TextInput{10, ecs::Position{330, 130}, "ROOM 1"});
        this->m_world.assign(TitleRoom1, ecs::Scale{1, 1});
        this->m_world.assign(TitleRoom1, ecs::Rotation{0});
        this->m_world.assign(TitleRoom1, ecs::Color{160, 160, 160, 255});
        this->m_world.assign(TitleRoom1, ecs::FontSize{30});
        this->m_world.assign(TitleRoom1, ecs::TextColor{0, 0, 0, 255});

        ecs::Entity &ButtonCreateRoom = this->m_world.createEntity(scene);
        this->m_world.assign(ButtonCreateRoom, ecs::Position{810, 900});
        this->m_world.assign(ButtonCreateRoom, ecs::Sprite{"assets/CreateRoom/buttonSettings.png", ecs::Rectangle{0, 0, 300, 153}, ecs::Vector2{0, 0}});
        this->m_world.assign(ButtonCreateRoom, ecs::Scale{1, 1});
        this->m_world.assign(ButtonCreateRoom, ecs::Rotation{0});
        this->m_world.assign(ButtonCreateRoom, ecs::Clickable{false, [this](ecs::Clickable&) {
            std::cout << "-> ButtonPlay clicked" << std::endl;
            std::cout << "Switch scene create room" << std::endl;
            loadCreateRoom(this->m_world.getSceneById(SCENE_CREATEROOM));
            this->m_world.switchToScene(SCENE_CREATEROOM);
        }});
    }
}
