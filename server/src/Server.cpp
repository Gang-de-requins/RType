/*
** EPITECH PROJECT, 2023
** r type
** File description:
** Server
*/

#include <iostream>
#include <boost/asio.hpp>
#include "../include/Server.hpp"
#include <iomanip>

serverGame::Server::Server()
{
}

serverGame::Server::~Server()
{

}

void serverGame::Server::setupServer(int port)
{
    this->endpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port);
    this->socket = std::make_shared<boost::asio::ip::udp::socket>(this->service, this->endpoint);
}

void serverGame::Server::receiveMessage()
{
    try
    {
        boost::asio::ip::udp::endpoint senderEndpoint;
        std::array<char, 1024> receiveBuffer;

        std::size_t bytes_transferred = this->socket->receive_from(boost::asio::buffer(receiveBuffer), senderEndpoint);

        if (bytes_transferred > 0)
        {
            std::cout << "Received binary message from client:";

            for (std::size_t i = 0; i < bytes_transferred; ++i)
            {
                std::cout << " 0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(static_cast<unsigned char>(receiveBuffer[i]));
            }

            std::cout << std::endl;
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception in receiveMessage: " << e.what() << std::endl;
    }
}

