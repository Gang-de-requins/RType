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

namespace game
{

    class Pong
    {
    public:
        Pong();
        ~Pong();
        void run();

    private:
        int _points;
    };

}

#endif /* !PONG_HPP__ */