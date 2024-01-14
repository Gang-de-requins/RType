/*
** EPITECH PROJECT, 2024
** RType
** File description:
** Pong
*/

#ifndef PONG_HPP__
#define PONG_HPP__

#include <iostream>
#include "systems/Controllable.hpp"
#include "systems/Movement.hpp"
#include "GameEngine.hpp"
#include "raylib.h"
#include "Events.hpp"

namespace game
{

    class Pong
    {
    ecs::World world;
    std::string name1;
    std::string name2;
    std::string winner;
    public:
        Pong();
        ~Pong();
        void run();
        bool CheckBallPos(ecs::SceneManager &sceneManager);

    private:
        void GameScenes();
        void LoadMenu(ecs::Scene &scene);
        void LoadGame(ecs::Scene &scene);
        void LoadEnd(ecs::Scene &scene);
        void LoadSettings(ecs::Scene &scene);
    };

}

#endif /* !PONG_HPP__ */