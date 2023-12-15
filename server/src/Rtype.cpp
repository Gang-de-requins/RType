/*
** EPITECH PROJECT, 2023
** r type
** File description:
** Server
*/

#include <iostream>
#include <boost/asio.hpp>
#include "Rtype.hpp"
#include "Network.hpp"

serverGame::Rtype::Rtype()
{
    this->server.setupServer(12345);
    this->id = 0;
}

serverGame::Rtype::~Rtype()
{

}

void serverGame::Rtype::run(void)
{
    while(true)
    {
        processMessages();
    }
}

void serverGame::Rtype::processMessages(void)
{
    while (this->msgList.size() != 0)
    {
        this->mutex.lock();
        serverGame::Message msg = this->msgList.front();
        this->msgList.erase(this->msgList.begin());
        this->mutex.unlock();

        if (msg.getMessageType() == Network::MessageType::PlayerJoin)
            addPlayer(msg);
    }
}

void serverGame::Rtype::addPlayer(serverGame::Message msg)
{
    this->id++;
    Player newPlayer(msg.getMessage(), this->id, this->world);
    newPlayer.setEndpoint(msg.getEndpoint());
    players.push_back(newPlayer);

    serverGame::Message playerJoinMessage;
    playerJoinMessage.setMessageType(Network::MessageType::PlayerJoin);
    playerJoinMessage.setMessage(newPlayer.getName());

    for (auto& player : this->players) {
        if (player.getId() != newPlayer.getId()) {
            std::string playerNameMessage = player.getName();
            serverGame::Message existingPlayerMessage;
            existingPlayerMessage.setMessageType(Network::MessageType::PlayerJoin);
            existingPlayerMessage.setMessage(playerNameMessage);
            this->server.sendMessage(existingPlayerMessage, newPlayer.getEndpoint());

            this->server.sendMessage(playerJoinMessage, player.getEndpoint());
        }
    }
}


