/*
** EPITECH PROJECT, 2024
** RType
** File description:
** Pong
*/

#ifndef PONG_HPP__
#define PONG_HPP__

#include <iostream>
#include "GameEngine.hpp"
#include "raylib.h"

namespace game
{

    class Pong
    {
    ecs::World world;
    std::string name1;
    std::string name2;
    public:
        Pong();
        ~Pong();
        void run();

    private:
        void GameScenes();
    };

}

#endif /* !PONG_HPP__ */