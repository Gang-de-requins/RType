/*
** EPITECH PROJECT, 2023
** r type
** File description:
** Server
*/

#include <iostream>
#include <boost/asio.hpp>
#include "../include/Server.hpp"
#include "Network.hpp"
#include <iomanip>
#include "Message.hpp"

serverGame::Server::Server()
{
}

serverGame::Server::~Server()
{

}

void serverGame::Server::setupServer(int port)
{
    this->endpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port);
    this->socket = std::make_shared<boost::asio::ip::udp::socket>(this->service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port));
}

void serverGame::Server::receiveMessage(Message &message) {
    try {
        boost::asio::ip::udp::endpoint senderEndpoint;
        std::array<char, 1024> receiveBuffer;

        std::size_t bytes_transferred = this->socket->receive_from(boost::asio::buffer(receiveBuffer), senderEndpoint);

        if (bytes_transferred > 0) {
            if(bytes_transferred >= sizeof(Network::MessageType)) {
                Network::MessageType messageType = *reinterpret_cast<Network::MessageType*>(&receiveBuffer[0]);
                message.setMessageType(messageType);
                std::string msg(receiveBuffer.data() + sizeof(Network::MessageType), bytes_transferred - sizeof(Network::MessageType));
                message.setMessage(msg);
                message.setEndpoint(senderEndpoint);
                std::cout << "Message: " << msg << std::endl;
            }
        }
    } catch (std::exception &e) {
        std::cerr << "Exception in receiveMessage: " << e.what() << std::endl;
    }
}

void serverGame::Server::sendMessage(const serverGame::Message &message, const boost::asio::ip::udp::endpoint &recipientEndpoint) {
    try {
        std::vector<char> sendBuffer;

        Network::MessageType messageType = message.getMessageType();
        sendBuffer.insert(sendBuffer.end(), reinterpret_cast<const char*>(&messageType), reinterpret_cast<const char*>(&messageType) + sizeof(Network::MessageType));

        std::string messagePayload = message.getMessage();
        sendBuffer.insert(sendBuffer.end(), messagePayload.begin(), messagePayload.end());

        socket->send_to(boost::asio::buffer(sendBuffer), recipientEndpoint);
    } catch (std::exception &e) {
        std::cerr << "Exception in sendMessage: " << e.what() << std::endl;
    }
}
