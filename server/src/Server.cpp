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
    // this->context = boost::asio::io_context();
    this->socket = std::make_shared<boost::asio::ip::udp::socket>(this->context, boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), port));
    this->context.run();
    this->service.run();
    // std::cout << "Endpoint: " << this->endpoint << std::endl;

    // this->endpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string("172.18.101.26"), 4444);
    // this->socket = std::make_shared<boost::asio::ip::udp::socket>(this->service, this->endpoint);
    // this->socket->bind(this->endpoint, this->ec);
    // this->socket->set_option(boost::asio::ip::udp::socket::reuse_address(true));

    // if (this->ec) {
    //     std::cerr << "Error binding socket: " << this->ec.message() << std::endl;
    // }
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
