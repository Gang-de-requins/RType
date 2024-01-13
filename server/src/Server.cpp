/*
** EPITECH PROJECT, 2023
** r type
** File description:
** Server
*/

#include <iostream>
#include "../include/Server.hpp"
#include "Network.hpp"
#include <iomanip>
#include "Message.hpp"
#include "GameEngine.hpp"

serverGame::Server::Server()
{
}

serverGame::Server::~Server()
{

}

void serverGame::Server::setupServer(int port)
{
    this->endpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), boost::asio::ip::port_type(port));
    this->socket = std::make_shared<boost::asio::ip::udp::socket>(this->service, this->endpoint);
}


void serverGame::Server::receiveMessage(ecs::Message &message) {
    std::vector<char> buffer(1024);
    boost::asio::ip::udp::endpoint sender_endpoint;

    std::size_t length = this->socket->receive_from(boost::asio::buffer(buffer), sender_endpoint);

    if (length >= sizeof(std::size_t) + sizeof(ecs::MessageType)) {
        std::size_t dataSize;
        ecs::MessageType messageType;
        std::memcpy(&dataSize, buffer.data(), sizeof(dataSize));
        std::memcpy(&messageType, buffer.data() + sizeof(dataSize), sizeof(messageType));

        message.setMessageType(messageType);

        if (length >= sizeof(dataSize) + sizeof(messageType)) {
            std::vector<char> messageData(buffer.begin() + sizeof(dataSize) + sizeof(messageType), 
                                            buffer.begin() + sizeof(dataSize) + sizeof(messageType) + dataSize);
            message.setMessageData(messageData);
        }
        message.setEndpoint(sender_endpoint);
    }
}

// void serverGame::Server::sendMessage(ecs::Buffer& buffer, const boost::asio::ip::udp::endpoint& recipientEndpoint) {
//     try {
//         const std::vector<char>& sendBuffer = buffer.getData();

//         socket->send_to(boost::asio::buffer(sendBuffer), recipientEndpoint);
//     } catch (std::exception& e) {
//         std::cerr << "Exception in sendMessage: " << e.what() << std::endl;
//     }
// }
