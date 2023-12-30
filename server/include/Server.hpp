/*
** EPITECH PROJECT, 2023
** r type
** File description:
** Server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <iostream>
#if defined(_WIN32)
    #define NOGDI
    #define NOUSER
#endif

#include <boost/asio.hpp>

#if defined(_WIN32)
    #undef near
    #undef far
#endif
#include "Message.hpp"

namespace serverGame
{
    class Server
    {
    public:
        Server();
        ~Server();
        void setupServer(int port);
        void receiveMessage(serverGame::Message &message);
        void sendMessage(const serverGame::Message &message, const boost::asio::ip::udp::endpoint &recipientEndpoint);

    private:
        std::shared_ptr<boost::asio::ip::udp::socket> socket;
        boost::asio::ip::udp::endpoint endpoint;
        boost::asio::io_service service;
        //std::vector<Client> clients;
    };
}

#endif /* !SERVER_HPP_ */
