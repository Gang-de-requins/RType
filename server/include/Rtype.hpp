/*
** EPITECH PROJECT, 2023
** r type
** File description:
** Server
*/

#ifndef RTYPE_HPP_
#define RTYPE_HPP_

#include <iostream>
#include "Server.hpp"
#include "Player.hpp"
#include "Message.hpp"
#include "GameEngine.hpp"
#include <mutex>

namespace serverGame
{
    class Rtype
    {
    public:
        Rtype(int port);
        ~Rtype();
        void run(void);
        void addPlayer(serverGame::Message msg);
        void addMissile(serverGame::Message msg);
        void GoDirection(serverGame::Message msg, Network::MessageType dir);
        void StopDirection(serverGame::Message msg, Network::MessageType dir);
        void processMessages(void);
        
        Server server;
        std::vector<serverGame::Message> msgList;
        std::mutex mutex;


    private:
        std::vector<Player> players;
        ecs::World world;
        int id;
    };
}

#endif /* !RTYPE_HPP_ */
