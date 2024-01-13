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
#include "GameEngine.hpp"

namespace serverGame
{
    class Server
    {
    public:
        Server();
        ~Server();
        void setupServer(int port);
        //void receiveMessage(serverGame::Message &message);
        void receiveMessage(ecs::Message &message);
        template <typename T>
        void send(T &data, ecs::MessageType messageType, const boost::asio::ip::udp::endpoint& recipientEndpoint) {
            std::vector<char> serializedData = data.serialize();
            std::size_t dataSize = serializedData.size();

            std::vector<char> packet(sizeof(std::size_t) + sizeof(ecs::MessageType) + dataSize);
            std::memcpy(packet.data(), &dataSize, sizeof(dataSize));
            std::memcpy(packet.data() + sizeof(dataSize), &messageType, sizeof(messageType));
            std::memcpy(packet.data() + sizeof(dataSize) + sizeof(ecs::MessageType), serializedData.data(), dataSize);

            this->socket->send_to(boost::asio::buffer(packet), recipientEndpoint);
        }
        void processReceivedStruct(ecs::MessageType messageType, const std::vector<char> &receiveBuffer);
        //void handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred,
        //            boost::asio::ip::udp::socket &socket, ecs::MessageType messageType);
        //void sendMessage(ecs::Buffer &buffer, const boost::asio::ip::udp::endpoint &recipientEndpoint);

    private:
        std::shared_ptr<boost::asio::ip::udp::socket> socket;
        boost::asio::ip::udp::endpoint endpoint;
        boost::asio::io_service service;
        //std::vector<Client> clients;
    };
}

#endif /* !SERVER_HPP_ */
