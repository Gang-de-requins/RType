#include "Game.hpp"

namespace rtype {
    void Game::loadChooseName(ecs::Scene &scene)
    {
        this->m_world.registerSystems<
            ecs::MusicSystem,
            ecs::ControllableSystem,
            ecs::MovementSystem,
            ecs::CollisionSystem,
            ecs::LifeSystem,
            ecs::ParallaxSystem,
            ecs::RenderSystem,
            ecs::ClickableSystem,
            ecs::TextInputSystem,
            ecs::SubmitSystem
        >(scene);

        std::cout << "In Choose Name" << std::endl;

        ecs::Entity &Bakckground_2 = this->m_world.createEntity(scene);
        this->m_world.assign(Bakckground_2, ecs::Position{0, 0});
        this->m_world.assign(Bakckground_2, ecs::Sprite{"assets/Menu/Space-Back-Menu.png", ecs::Rectangle{0, 0, 1920, 1080}, ecs::Vector2{0, 0}});
        this->m_world.assign(Bakckground_2, ecs::Scale{1, 1});
        this->m_world.assign(Bakckground_2, ecs::Rotation{0});

        ecs::Entity &PlayerTextInput = this->m_world.createEntity(scene);
        this->m_world.assign(PlayerTextInput, ecs::Position{500, 300});
        this->m_world.assign(PlayerTextInput, ecs::Rectangle{0, 0, 300, 100});
        this->m_world.assign(PlayerTextInput, ecs::TextInput{10, ecs::Position{500, 325}});
        this->m_world.assign(PlayerTextInput, ecs::Scale{1, 1});
        this->m_world.assign(PlayerTextInput, ecs::Rotation{0});
        this->m_world.assign(PlayerTextInput, ecs::Clickable{false, [this](ecs::Clickable&) {
            ecs::Entity &PlayerTextInput = this->m_world.getEntityById(this->m_world.getCurrentScene(), 1);
            ecs::TextInput &textInput = this->m_world.get<ecs::TextInput>(PlayerTextInput);

            textInput.isFocused = true;
        }});
        this->m_world.assign(PlayerTextInput, ecs::Color{200, 200, 200, 255});
        this->m_world.assign(PlayerTextInput, ecs::FontSize{50});
        this->m_world.assign(PlayerTextInput, ecs::TextColor{255, 255, 255, 255});
        this->m_world.assign(PlayerTextInput, ecs::Submit{KEY_ENTER, [this](ecs::SceneManager &sceneManager, ecs::Entity *entity) {
            if (sceneManager.has<ecs::TextInput>(*entity)) {
                ecs::TextInput &textInput = sceneManager.get<ecs::TextInput>(*entity);
                this->m_playerName = textInput.content;
                std::cout << "player name: " << this->m_playerName << std::endl;
            }
        }});

        ecs::Entity &ButtonPlay = this->m_world.createEntity(scene);
        this->m_world.assign(ButtonPlay, ecs::Position{810, 300});
        this->m_world.assign(ButtonPlay, ecs::Sprite{"assets/Menu/buttonPlay.png", ecs::Rectangle{0, 0, 300, 153}, ecs::Vector2{0, 0}});
        this->m_world.assign(ButtonPlay, ecs::Scale{1, 1});
        this->m_world.assign(ButtonPlay, ecs::Rotation{0});
        this->m_world.assign(ButtonPlay, ecs::Clickable{false, [this](ecs::Clickable&) {
            std::cout << "-> ButtonPlay clicked" << std::endl;
            std::cout << "Switch scene to play game" << std::endl;
            loadGame(this->m_world.getSceneById(SCENE_GAME));
            this->m_world.switchToScene(SCENE_GAME);
        }});
    }
}
