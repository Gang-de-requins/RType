/*
** EPITECH PROJECT, 2023
** r type
** File description:
** Server
*/

#ifndef SERVERROOMS_HPP_
#define SERVERROOMS_HPP_

#include <iostream>
#include <list>
#if defined(_WIN32)
    #define NOGDI
    #define NOUSER
#endif

#include <boost/asio.hpp>

#if defined(_WIN32)
    #undef near
    #undef far
#endif
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
        void getRooms(boost::asio::ip::udp::endpoint endpoint);

    private:
    struct RoomInfo {
            std::string name;
            int port;
            int availableSlots;
        };
        Server server;
        std::vector<std::thread> threadPool;
        std::vector<ecs::RoomInfo> rooms;
        std::mutex roomsMutex;
        int port;
    };
}

#endif /* !SERVERROOMS_HPP_ */
