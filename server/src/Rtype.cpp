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
        ecs::ControllableSystem,
        ecs::MovementSystem,
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
        this->world.update();
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

        ecs::MessageType messageType = buffer.readMessageType();
        std::string messageString = buffer.readString();

        auto it = std::find_if(this->entities.begin(), this->entities.end(), [buffer, messageString](const Entity &entity) {
            return entity.getName() == messageString;
        });

        if (messageType == ecs::MessageType::PlayerJoin) {
            addPlayer(messageString, buffer.getEndpoint());
            return;
        }

        if (it != this->entities.end()) {
            Entity& matchingPlayer = *it;
            switch (messageType)
            {
                case ecs::MessageType::GoRight:
                    matchingPlayer.move(messageString, ecs::MessageType::GoRight, this->world);
                    break;
                case ecs::MessageType::GoLeft:
                    matchingPlayer.move(messageString, ecs::MessageType::GoLeft, this->world);
                    break;
                case ecs::MessageType::GoTop:
                    matchingPlayer.move(messageString, ecs::MessageType::GoTop, this->world);
                    break;
                case ecs::MessageType::GoBottom:
                    matchingPlayer.move(messageString, ecs::MessageType::GoBottom, this->world);
                    break;
                // case ecs::MessageType::StopRight:
                //     StopDirection(msg, ecs::MessageType::StopRight);
                //     break;
                // case ecs::MessageType::StopLeft:
                //     StopDirection(msg, ecs::MessageType::StopLeft);
                //     break;
                // case ecs::MessageType::StopTop:
                //     StopDirection(msg, ecs::MessageType::StopTop);
                //     break;
                // case ecs::MessageType::StopBottom:
                //     StopDirection(msg, ecs::MessageType::StopBottom);
                //     break;
                default:
                    break;
            }
        }
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

void serverGame::Rtype::addPlayer(std::string name, boost::asio::ip::udp::endpoint endpoint)
{
    this->id++;
    ecs::Scene &inGame = world.getCurrentScene();
    ecs::Entity &entity = world.createEntity(inGame);

    world.assign(entity, ecs::Position{200, 200});
    world.assign(entity, ecs::Health{100});
    world.assign(entity, ecs::Velocity{0, 0});
    world.assign(entity, ecs::Sprite{"assets/characters.gif", ecs::Rectangle{0, 0, 32, 16}, ecs::Vector2{0, 0}});
    world.assign(entity, ecs::Acceleration{0, 0, 4});
    world.assign(entity, ecs::Scale{1, 1});
    world.assign(entity, ecs::Rotation{0});
    world.assign(entity, ecs::Controllable{KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT});
    world.assign(entity, ecs::Collision{false, {}});
    world.assign(entity, ecs::Animation{ecs::Rectangle{0, 0, 32, 0}, 4, 0, 300, std::chrono::steady_clock::now()});
    world.assign(entity, ecs::Name{name, ecs::Position{-20, -20}});

    serverGame::Entity newEntity(name, this->id, this->world, entity);
    newEntity.setEndpoint(endpoint);
    newEntity.setType("PLAYER");
    this->mutex.lock();
    this->entities.push_back(newEntity);
    this->mutex.unlock();

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
    this->mutex.lock();
    for (auto &entity : this->getEntities()) {
        if (entity.getType() == "PLAYER") {
            for (auto& entity : this->getEntities()) {
                std::pair<float, float> pos = entity.getPosition(this->world);
                ecs::Buffer newBuffer;
                newBuffer.writeMessageType(ecs::MessageType::Ping);
                std::string posStr = std::to_string(pos.first) + "," + std::to_string(pos.second);
                newBuffer.writeString(entity.getType() + entity.getName() + posStr);
                this->server.sendMessage(newBuffer, entity.getEndpoint());
            }
        }
    }
    this->mutex.unlock();
}
