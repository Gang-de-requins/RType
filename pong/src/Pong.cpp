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
            ecs::RenderSystem,
            ecs::ClickableSystem,
            ecs::TextSystem
        >(inMenu);

        /* Menu Text Entity */
        ecs::Entity &Pong = this->world.createEntity(inMenu);
        this->world.assign(Pong, ecs::Position{800, 50});
        this->world.assign(Pong, ecs::Sprite{"../assets/pong.png", ecs::Rectangle{0, 0, 500, 500}, ecs::Vector2{0, 0}});
        this->world.assign(Pong, ecs::Scale{0.7, 0.7});
        this->world.assign(Pong, ecs::Rotation{0});


        /* Player 1 Name Entity */
        ecs::Entity &NamePlayer1 = this->world.createEntity(inMenu);

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

        /* Player 2 Name Entity */
        ecs::Entity &NamePlayer2 = this->world.createEntity(inMenu);

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

        /* Play Button Entity */
        ecs::Entity &ButtonPlay = this->world.createEntity(inMenu);
        this->world.assign(ButtonPlay, ecs::Position{870, 700});
        this->world.assign(ButtonPlay, ecs::Sprite{"../assets/p_play.png", ecs::Rectangle{0, 0, 100, 41}, ecs::Vector2{0, 0}});
        this->world.assign(ButtonPlay, ecs::Scale{2, 2});
        this->world.assign(ButtonPlay, ecs::Rotation{0});
        this->world.assign(ButtonPlay, ecs::Clickable{false, [this](ecs::Clickable&) {
            std::cout << "ButtonPlay clicked" << std::endl;
            std::cout << "Player1: " << this->name1 << std::endl << "Player2: " << this->name2 << std::endl;
            this->world.switchToScene(1);
        }});

        
        /* Menu Music Entity */
        ecs::Entity &MenuMusic = this->world.createEntity(inMenu);
        this->world.assign(MenuMusic, ecs::Music({"../assets/pong_menu.wav", 0.1f, true}));


        /* ------------------------- Game --------------------------------*/

        /* Game Scene */
        ecs::Scene &inGame = this->world.createScene();

        /* Game Systems */
        this->world.registerSystems<
            ecs::MusicSystem,
            ecs::ControllableSystem,
            ecs::RenderSystem,
            ecs::ClickableSystem,
            ecs::TextSystem,
            ecs::AnimationSystem,
            ecs::MovementSystem,
            ecs::SoundSystem
        >(inMenu);

        /* Map background */
        ecs::Entity &Background = this->world.createEntity(inGame);
        this->world.assign(Pong, ecs::Position{0, 0});
        this->world.assign(Pong, ecs::Sprite{"../assets/pong_map.png", ecs::Rectangle{0, 0, 1920, 1080}, ecs::Vector2{0, 0}});
        this->world.assign(Pong, ecs::Scale{1, 1});
        this->world.assign(Pong, ecs::Rotation{0});


        ecs::Entity &p1 = this->world.createEntity(inGame);
        this->world.assign(p1, ecs::Position{500, 500});
        this->world.assign(p1, ecs::Sprite{"../assets/player1.png", ecs::Rectangle{0, 0, 74, 539}, ecs::Vector2{0, 0}});
        this->world.assign(p1, ecs::Scale{1, 1});
        this->world.assign(p1, ecs::Rotation{0});


        ecs::Entity &p2 = this->world.createEntity(inGame);
        this->world.assign(p2, ecs::Position{0, 0});
        this->world.assign(p2, ecs::Sprite{"../assets/player2.png", ecs::Rectangle{0, 0, 67, 594}, ecs::Vector2{0, 0}});
        this->world.assign(p2, ecs::Scale{1, 1});
        this->world.assign(p2, ecs::Rotation{0});
    }
}