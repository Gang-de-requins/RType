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

void serverGame::Server::receiveMessage(ecs::Buffer& buffer) {
    try {
        boost::asio::ip::udp::endpoint senderEndpoint;
        std::array<char, 1024> receiveBuffer;

        std::size_t bytes_transferred = this->socket->receive_from(boost::asio::buffer(receiveBuffer), senderEndpoint);

        if (bytes_transferred > 0) {
            buffer.setData(std::vector<char>(receiveBuffer.begin(), receiveBuffer.begin() + bytes_transferred));
            buffer.setEndpoint(senderEndpoint);
        }
    } catch (std::exception &e) {
        std::cerr << "Exception in receiveMessage: " << e.what() << std::endl;
    }
}


// void serverGame::Server::sendMessage(const serverGame::Message &message, const boost::asio::ip::udp::endpoint &recipientEndpoint) {
//     try {
//         std::vector<char> sendBuffer;

//         Network::MessageType messageType = message.getMessageType();
//         sendBuffer.insert(sendBuffer.end(), reinterpret_cast<const char*>(&messageType), reinterpret_cast<const char*>(&messageType) + sizeof(Network::MessageType));

//         std::string messagePayload = message.getMessage();
//         sendBuffer.insert(sendBuffer.end(), messagePayload.begin(), messagePayload.end());

//         socket->send_to(boost::asio::buffer(sendBuffer), recipientEndpoint);
//     } catch (std::exception &e) {
//         std::cerr << "Exception in sendMessage: " << e.what() << std::endl;
//     }
// }

void serverGame::Server::sendMessage(ecs::Buffer& buffer, const boost::asio::ip::udp::endpoint& recipientEndpoint) {
    try {
        const std::vector<char>& sendBuffer = buffer.getData();

        socket->send_to(boost::asio::buffer(sendBuffer), recipientEndpoint);
    } catch (std::exception& e) {
        std::cerr << "Exception in sendMessage: " << e.what() << std::endl;
    }
}
