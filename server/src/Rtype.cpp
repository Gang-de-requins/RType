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
    while (!this->bufferList.empty())
    {
        this->mutex.lock();
        ecs::Buffer buffer = this->bufferList.front();
        this->bufferList.erase(this->bufferList.begin());
        this->mutex.unlock();

        std::cout << buffer.readString() << std::endl;

        auto it = std::find_if(this->entities.begin(), this->entities.end(), [&buffer](const Entity& entity) {
            return entity.getName() == buffer.readString();
        });

        if (buffer.readMessageType() == ecs::MessageType::PlayerJoin) {
            addPlayer(buffer);
            return;
        }

        // if (it != this->entities.end()) {
        //     Entity& matchingPlayer = *it;
        //     switch (msg.getMessageType())
        //     {
        //         case Network::MessageType::GoRight:
        //             GoDirection(msg, Network::MessageType::GoRight);
        //             matchingPlayer.move(msg.getMessage(), Network::MessageType::GoRight, this->world);
        //             break;
        //         case Network::MessageType::GoLeft:
        //             GoDirection(msg, Network::MessageType::GoLeft);
        //             break;
        //         case Network::MessageType::GoTop:
        //             GoDirection(msg, Network::MessageType::GoTop);
        //             break;
        //         case Network::MessageType::GoBottom:
        //             GoDirection(msg, Network::MessageType::GoBottom);
        //             break;
        //         case Network::MessageType::StopRight:
        //             StopDirection(msg, Network::MessageType::StopRight);
        //             break;
        //         case Network::MessageType::StopLeft:
        //             StopDirection(msg, Network::MessageType::StopLeft);
        //             break;
        //         case Network::MessageType::StopTop:
        //             StopDirection(msg, Network::MessageType::StopTop);
        //             break;
        //         case Network::MessageType::StopBottom:
        //             StopDirection(msg, Network::MessageType::StopBottom);
        //             break;
        //         default:
        //             break;
        //     }
        // }
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
        // for (auto& player : this->players) {
        //     if (player.getEndpoint() != msg.getEndpoint()) {
        //         this->server.sendMessage(goRightMessage, player.getEndpoint());
        //     }
        // }
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
        // for (auto& player : this->players) {
        //     if (player.getEndpoint() != msg.getEndpoint()) {
        //         this->server.sendMessage(goRightMessage, player.getEndpoint());
        //     }
        // }
    }
}

void serverGame::Rtype::addPlayer(ecs::Buffer msg)
{
    this->id++;
    serverGame::Entity newEntity(msg.readString(), this->id, this->world);
    newEntity.setEndpoint(msg.getEndpoint());
    newEntity.setType("PLAYER");
    this->entities.push_back(newEntity);

    ecs::Buffer playerJoinMessage;
    playerJoinMessage.writeMessageType(ecs::MessageType::PlayerJoin);
    playerJoinMessage.writeString(newEntity.getName());

    for (auto& entity : this->entities) {
        if (entity.getName() != newEntity.getName()) {
            std::string playerNameMessage = entity.getName();
            ecs::Buffer existingPlayerMessage;
            existingPlayerMessage.writeMessageType(ecs::MessageType::PlayerJoin);
            existingPlayerMessage.writeString(playerNameMessage);

            this->server.sendMessage(existingPlayerMessage, newEntity.getEndpoint());
            this->server.sendMessage(playerJoinMessage, entity.getEndpoint());
        }
    }
}

void serverGame::Rtype::sendGameState()
{
    for (auto& entity : this->getEntities()) {
        if (entity.getType() == "PLAYER") {
            for (auto& entity : this->getEntities()) {
                std::pair<float, float> pos = entity.getPosition(this->world);
                serverGame::Message message;
                message.setMessageType(Network::MessageType::Ping);

                std::string posStr = std::to_string(pos.first) + "," + std::to_string(pos.second);
                message.setMessage(entity.getType() + entity.getName() + posStr);

                ///this->server.sendMessage(message, entity.getEndpoint());
            }
        }
    }
}
