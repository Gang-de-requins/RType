/*
** EPITECH PROJECT, 2023
** r type
** File description:
** Server
*/

#ifndef SERVERROOMS_HPP_
#define SERVERROOMS_HPP_

#include <iostream>
#include <boost/asio.hpp>
#include "Server.hpp"

namespace serverGame
{
    class ServerRooms
    {
    public:
        ServerRooms();
        ~ServerRooms();
        void start();
        void createRoom(std::string const roomName);

    private:
        Server server;
        std::vector<std::thread> threadPool;
    };
}

#endif /* !SERVERROOMS_HPP_ */
