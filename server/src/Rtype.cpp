/*
** EPITECH PROJECT, 2023
** r type
** File description:
** Server
*/

#include <iostream>
#include <boost/asio.hpp>
#include "Rtype.hpp"

serverGame::Rtype::Rtype(int port)
{
    this->server.setupServer(port);
    this->id = 0;
}

serverGame::Rtype::~Rtype()
{

}

void serverGame::Rtype::run(void)
{
    while(true)
    {
        this->server.receiveMessage();
    }
}

void serverGame::Rtype::addPlayer(std::string name)
{
    this->id++;
    name = "test";
    // Player newPlayer(name, this->id, this->world);
    // players.push_back(newPlayer);
}