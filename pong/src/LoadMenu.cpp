/*
** EPITECH PROJECT, 2024
** RType
** File description:
** LoadMenu
*/

#include "Pong.hpp"

namespace game 
{

    void Pong::LoadMenu(ecs::Scene &scene)
    {
        /* Menu Systems */
        this->world.registerSystems<
            ecs::MusicSystem,
            ecs::RenderSystem,
            ecs::ClickableSystem,
            ecs::SubmitSystem
        >(scene);

        /* Menu Text Entity */
        ecs::Entity &Pong = this->world.createEntity(scene);
        this->world.assign(Pong, ecs::Position{800, 50});
        this->world.assign(Pong, ecs::Sprite{"../assets/pong.png", ecs::Rectangle{0, 0, 500, 500}, ecs::Vector2{0, 0}});
        this->world.assign(Pong, ecs::Scale{0.7, 0.7});
        this->world.assign(Pong, ecs::Rotation{0});


        /* Player 1 Name Entity */
        ecs::Entity &NamePlayer1 = this->world.createEntity(scene);

        this->world.assign(NamePlayer1, ecs::Position{625, 400});
        this->world.assign(NamePlayer1, ecs::Rectangle{0, 0, 300, 100});
        this->world.assign(NamePlayer1, ecs::TextInput{10, ecs::Position{660, 425}, "Player1"});
        this->world.assign(NamePlayer1, ecs::Scale{1, 1});
        this->world.assign(NamePlayer1, ecs::Rotation{0});
        this->world.assign(NamePlayer1, ecs::Clickable{false, [this](ecs::Clickable&) {
            std::cout << "NamePlayer1 clicked" << std::endl;
            ecs::Entity &NamePlayer1 = this->world.getEntityById(this->world.getCurrentScene(), 1);
            ecs::TextInput &textInput = this->world.get<ecs::TextInput>(NamePlayer1);

            this->name1 = textInput.content;
            textInput.isFocused = true;
        }});
        this->world.assign(NamePlayer1, ecs::Color{200, 200, 200, 255});
        this->world.assign(NamePlayer1, ecs::FontSize{50});
        this->world.assign(NamePlayer1, ecs::TextColor{0, 0, 0, 255});
        this->world.assign(NamePlayer1, ecs::Submit{KEY_ENTER, [this](ecs::SceneManager &sceneManager, ecs::Entity *entity) {
            if (sceneManager.has<ecs::TextInput>(*entity)) {
                ecs::TextInput &textInput = sceneManager.get<ecs::TextInput>(*entity);
                this->name1 = textInput.content;
                std::cout << "player 1 name: " << this->name1 << std::endl;
            }
        }});


        /* Player 2 Name Entity */
        ecs::Entity &NamePlayer2 = this->world.createEntity(scene);

        this->world.assign(NamePlayer2, ecs::Position{1025, 400});
        this->world.assign(NamePlayer2, ecs::Rectangle{0, 0, 300, 100});
        this->world.assign(NamePlayer2, ecs::TextInput{10, ecs::Position{1060, 425}, "Player2"});
        this->world.assign(NamePlayer2, ecs::Scale{1, 1});
        this->world.assign(NamePlayer2, ecs::Rotation{0});
        this->world.assign(NamePlayer2, ecs::Clickable{false, [this](ecs::Clickable&) {
            std::cout << "NamePlayer2 clicked" << std::endl;
            ecs::Entity &NamePlayer2 = this->world.getEntityById(this->world.getCurrentScene(), 2);
            ecs::TextInput &textInput = this->world.get<ecs::TextInput>(NamePlayer2);

            this->name2 = textInput.content;
            textInput.isFocused = true;

        }});
        this->world.assign(NamePlayer2, ecs::Color{200, 200, 200, 255});
        this->world.assign(NamePlayer2, ecs::FontSize{50});
        this->world.assign(NamePlayer2, ecs::TextColor{0, 0, 0, 255});
        this->world.assign(NamePlayer2, ecs::Submit{KEY_ENTER, [this](ecs::SceneManager &sceneManager, ecs::Entity *entity) {
            if (sceneManager.has<ecs::TextInput>(*entity)) {
                ecs::TextInput &textInput = sceneManager.get<ecs::TextInput>(*entity);
                this->name2 = textInput.content;
                std::cout << "player 2 name: " << this->name2 << std::endl;
            }
        }});


        /* Play Button Entity */
        ecs::Entity &ButtonPlay = this->world.createEntity(scene);
        this->world.assign(ButtonPlay, ecs::Position{725, 700});
        this->world.assign(ButtonPlay, ecs::Sprite{"../assets/pong_play.png", ecs::Rectangle{0, 0, 245, 60}, ecs::Vector2{0, 0}});
        this->world.assign(ButtonPlay, ecs::Scale{2, 2});
        this->world.assign(ButtonPlay, ecs::Rotation{0});
        this->world.assign(ButtonPlay, ecs::Clickable{false, [this](ecs::Clickable&) {
            std::cout << "ButtonPlay clicked" << std::endl;
            std::cout << "Player1: " << this->name1 << std::endl << "Player2: " << this->name2 << std::endl;
            LoadGame(this->world.getSceneById(GAME));
            this->world.switchToScene(GAME);
        }});

        
        /* Menu Music Entity */
        // ecs::Entity &MenuMusic = this->world.createEntity(scene);
        // this->world.assign(MenuMusic, ecs::Music({"../assets/pong_menu.wav", 0.1f, true}));

    }
}