/*
** EPITECH PROJECT, 2023
** r type
** File description:
** Server
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <iostream>
#include <boost/asio.hpp>
#include "GameEngine.hpp"

namespace serverGame
{
    class Player
    {
    public:
        Player(std::string name, int id, ecs::World &world);
        ~Player();

    private:
        ecs::Entity entityChar;
        ecs::Entity entityName;
        int id;
        std::string name;
    };
}

#endif /* !PLAYER_HPP_ */
