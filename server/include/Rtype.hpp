/*
** EPITECH PROJECT, 2023
** r type
** File description:
** Server
*/

#ifndef RTYPE_HPP_
#define RTYPE_HPP_

#include <iostream>
#include <boost/asio.hpp>
#include "Server.hpp"
#include "Player.hpp"
#include "GameEngine.hpp"


namespace serverGame
{
    class Rtype
    {
    public:
        Rtype(int const port);
        ~Rtype();
        void run(void);
        void addPlayer(std::string name);

    private:
        Server server;
        std::vector<Player> players;
        ecs::World world;
        int id;
    };
}

#endif /* !RTYPE_HPP_ */
