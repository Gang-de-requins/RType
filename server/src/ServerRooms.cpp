/*
** EPITECH PROJECT, 2023
** r type
** File description:
** Server
*/

#include <iostream>
#include <boost/asio.hpp>
#include "../include/ServerRooms.hpp"

serverGame::ServerRooms::ServerRooms()
{
    this->server.setupServer(12345);
}

serverGame::ServerRooms::~ServerRooms()
{

}

void serverGame::ServerRooms::start()
{
    while(true)
    {
        ecs::Buffer buffer;
        this->server.receiveMessage(buffer);

        ecs::MessageType messageType = buffer.readMessageType();
        std::string messageString = buffer.readString();
        boost::asio::ip::udp::endpoint endpoint = buffer.getEndpoint();

        switch (messageType)
        {
            case ecs::MessageType::CreateRoom:
                this->createRoom(messageString);
                break;

            case ecs::MessageType::GetRooms:
                this->getRooms(endpoint);
                break;
        }
    }
}

void serverGame::ServerRooms::createRoom(std::string roomName)
{

}

void serverGame::ServerRooms::getRooms(boost::asio::ip::udp::endpoint endpoint)
{

}