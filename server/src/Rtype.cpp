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
#include "Entity.hpp"

serverGame::Rtype::Rtype()
{
    this->server.setupServer(12345);
    this->id = 0;
    ecs::Scene &inGame = this->world.createScene();
    this->world.registerSystems<
        ecs::MusicSystem,
        ecs::ControllableSystem,
        ecs::AnimationSystem,
        ecs::MovementSystem,
        ecs::SpriteSystem,
        ecs::NameSystem,
        ecs::TextSystem,
        ecs::CollisionSystem,
        ecs::LifeSystem
    >(inGame);
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

        std::cout << msg.getEndpoint() << std::endl;
        if (msg.getMessageType() == Network::MessageType::PlayerJoin)
            addPlayer(msg);
        if (msg.getMessageType() == Network::MessageType::GoRight)
            GoDirection(msg, Network::MessageType::GoRight);
        if (msg.getMessageType() == Network::MessageType::GoLeft)
            GoDirection(msg, Network::MessageType::GoLeft);
        if (msg.getMessageType() == Network::MessageType::GoTop)
            GoDirection(msg, Network::MessageType::GoTop);
        if (msg.getMessageType() == Network::MessageType::GoBottom)
            GoDirection(msg, Network::MessageType::GoBottom);

        if (msg.getMessageType() == Network::MessageType::StopRight)
            StopDirection(msg, Network::MessageType::StopRight);
        if (msg.getMessageType() == Network::MessageType::StopLeft)
            StopDirection(msg, Network::MessageType::StopLeft);
        if (msg.getMessageType() == Network::MessageType::StopTop)
            StopDirection(msg, Network::MessageType::StopTop);
        if (msg.getMessageType() == Network::MessageType::StopBottom)
            StopDirection(msg, Network::MessageType::StopBottom);
    }
}

void serverGame::Rtype::GoDirection(serverGame::Message msg, Network::MessageType dir)
{
    auto it = std::find_if(players.begin(), players.end(), [&msg](const Player& player) {
        return player.getEndpoint() == msg.getEndpoint();
    });

    if (it != players.end()) {
        const Player& matchingPlayer = *it;

        serverGame::Message goRightMessage;
        goRightMessage.setMessageType(dir);
        goRightMessage.setMessage(matchingPlayer.getName());
        for (auto& player : this->players) {
            if (player.getEndpoint() != msg.getEndpoint()) {
                this->server.sendMessage(goRightMessage, player.getEndpoint());
            }
        }
    }
}

void serverGame::Rtype::StopDirection(serverGame::Message msg, Network::MessageType dir)
{
    auto it = std::find_if(players.begin(), players.end(), [&msg](const Player& player) {
        return player.getEndpoint() == msg.getEndpoint();
    });

    if (it != players.end()) {
        const Player& matchingPlayer = *it;

        serverGame::Message goRightMessage;
        goRightMessage.setMessageType(dir);
        goRightMessage.setMessage(matchingPlayer.getName());
        for (auto& player : this->players) {
            if (player.getEndpoint() != msg.getEndpoint()) {
                this->server.sendMessage(goRightMessage, player.getEndpoint());
            }
        }
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


