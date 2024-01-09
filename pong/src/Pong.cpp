/*
** EPITECH PROJECT, 2024
** pong
** File description:
** Pong
*/

#include "Pong.hpp"

namespace game
{

    Pong::Pong()
    {
        this->GameScenes();
    }

    Pong::~Pong()
    {
        std::cout << "Game closed." << std::endl;
    }

    void Pong::run()
    {
        SetTraceLogLevel(LOG_NONE);
        InitAudioDevice();
        InitWindow(1920, 1080, "Pong");
        SetTargetFPS(60);

        std::cout << "Running game" << std::endl;
        while (!WindowShouldClose()) {
            BeginDrawing();
            ClearBackground(BLACK);
            this->world.update();
            EndDrawing();
        }
        CloseWindow();
        CloseAudioDevice();
    }

    void Pong::GameScenes()
    {
        /* ------------------------- Menu --------------------------------*/

        /* Menu Scene */
        ecs::Scene &inMenu = this->world.createScene();

        /* Menu Systems */
        this->world.registerSystems<
            ecs::MusicSystem,
            ecs::ControllableSystem,
            ecs::MovementSystem,
            ecs::CollisionSystem,
            ecs::LifeSystem,
            ecs::ParallaxSystem,
            ecs::RenderSystem,
            ecs::ClickableSystem,
            ecs::TextSystem
        >(inMenu);

        /* Menu Text Entity */
        ecs::Entity &Pong = this->world.createEntity(inMenu);
        this->world.assign(Pong, ecs::Position{650, 50});
        this->world.assign(Pong, ecs::Sprite{"../assets/pong.png", ecs::Rectangle{0, 0, 500, 500}, ecs::Vector2{0, 0}});
        this->world.assign(Pong, ecs::Scale{0.7, 0.7});
        this->world.assign(Pong, ecs::Rotation{0});


        /* Player 1 Name Entity */
        ecs::Entity &NamePlayer1 = this->world.createEntity(inMenu);

        this->world.assign(NamePlayer1, ecs::Position{500, 300});
        this->world.assign(NamePlayer1, ecs::Rectangle{0, 0, 300, 100});
        this->world.assign(NamePlayer1, ecs::TextInput{10, ecs::Position{500, 325}, "Player1"});
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

        /* Player 2 Name Entity */
        ecs::Entity &NamePlayer2 = this->world.createEntity(inMenu);

        this->world.assign(NamePlayer2, ecs::Position{900, 300});
        this->world.assign(NamePlayer2, ecs::Rectangle{0, 0, 300, 100});
        this->world.assign(NamePlayer2, ecs::TextInput{10, ecs::Position{900, 325}, "Player2"});
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


        ecs::Entity &ButtonPlay = this->world.createEntity(inMenu);
        this->world.assign(ButtonPlay, ecs::Position{500, 500});
        this->world.assign(ButtonPlay, ecs::Sprite{"../assets/buttonPlay.png", ecs::Rectangle{0, 0, 300, 153}, ecs::Vector2{0, 0}});
        this->world.assign(ButtonPlay, ecs::Scale{1, 1});
        this->world.assign(ButtonPlay, ecs::Rotation{0});
        this->world.assign(ButtonPlay, ecs::Clickable{false, [this](ecs::Clickable&) {
            std::cout << "ButtonPlay clicked" << std::endl;
            // this->world.switchToScene(1);
        }});
    }
}