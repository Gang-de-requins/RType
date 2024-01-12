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
        ecs::Scene &scene = this->world.createScene();

        LoadMenu(scene);

        /* ------------------------- Game --------------------------------*/

        this->world.createScene();

        /* ------------------------- End ---------------------------------*/

        this->world.createScene();

        /* ------------------------- Settings (maybe) --------------------------------*/

        this->world.createScene();

    }
}