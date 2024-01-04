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
#include "Entity.hpp"

namespace serverGame
{
    class Rtype
    {
    public:
        Rtype(int port);
        ~Rtype();
        void run(void);
        //void addPlayer(serverGame::Message msg);
        void addDefault(std::string name);
        void addPlayer(std::string name, boost::asio::ip::udp::endpoint endpoint);
        void addMissile(serverGame::Message msg);
        void GoDirection(serverGame::Message msg, Network::MessageType dir);
        void StopDirection(serverGame::Message msg, Network::MessageType dir);
        void processMessages(void);
        void sendGameState();
        void newEntity(std::string name);
        std::vector<Player> getPlayers()
        {
            return this->players;
        }
        std::vector<serverGame::Entity> &getEntities()
        {
            return this->entities;
        }
        
        Server server;
        std::vector<ecs::Buffer> bufferList;
        std::mutex mutex;


    private:
        std::vector<Player> players;
        std::vector<serverGame::Entity> entities;
        ecs::World world;
        ecs::Scene scene;
        int id;
    };
}

#endif /* !RTYPE_HPP_ */
