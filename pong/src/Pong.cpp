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
            if (this->CheckBallPos(this->world.getSceneManager()))
            {
                LoadEnd(this->world.getSceneById(END));
                this->world.switchToScene(END);
            }
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

    bool Pong::CheckBallPos(ecs::SceneManager &sceneManager) 
    {
        ecs::Scene &scene = sceneManager.getCurrentScene();
        std::vector<ecs::Entity*> list = sceneManager.view<ecs::Position, ecs::Velocity>(scene);
        // if (scene.id != GAME)
        //     return false;
        for (auto &entity : list)
        {
            ecs::Position &actualPos = sceneManager.get<ecs::Position>(*entity);
            ecs::Velocity &actualVel = sceneManager.get<ecs::Velocity>(*entity);

            if (actualVel.dx != 0 || actualVel.dy != 0)
            {
                if (actualPos.x <= 20)
                {
                    this->winner = this->name2;
                    return true;
                }
                else if (actualPos.x >= 1900)
                {
                    this->winner = this->name1;
                    return true;
                }
                else if (actualPos.y <= 5 || actualPos.y >= 1005)
                {
                    actualVel.dy *= -1;
                } 
            }
        }
        return false;
    }
}