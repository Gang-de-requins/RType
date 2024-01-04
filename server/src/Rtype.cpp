/*
** EPITECH PROJECT, 2023
** r type
** File description:
** Server
*/

#include <iostream>
#include "Rtype.hpp"
#include "Network.hpp"
#include "Entity.hpp"

serverGame::Rtype::Rtype(int port)
{
    this->server.setupServer(port);
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
    this->addDefault("test");
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    while(true)
    {
        this->world.update();
        processMessages();

        if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - begin).count() > 2000) {
            // std::cout << "Send new enemy" << std::endl;
            begin = std::chrono::steady_clock::now();
            
            serverGame::Message existingPlayerMessage;
            existingPlayerMessage.setMessageType(Network::MessageType::NewEnemy);
            existingPlayerMessage.setMessage("Position:800,800");

            for (auto& player : this->players) {
                // std::cout << "PLAYER ID: " << player.getId() << std::endl;
                if (player.getId() != 0) {
                    std::cout << "New enemy to send" << std::endl;
                    //this->server.sendMessage(existingPlayerMessage, player.getEndpoint());
                }
            }
        }
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
            Entity &matchingPlayer = *it;
            switch (messageType)
            {
                case ecs::MessageType::GoRight:
                    matchingPlayer.move(messageString, ecs::MessageType::GoRight, this->world);
                    break;
                // case ecs::MessageType::GoLeft:
                //     matchingPlayer.move(messageString, ecs::MessageType::GoLeft, this->world);
                //     break;
                // case ecs::MessageType::GoTop:
                //     matchingPlayer.move(messageString, ecs::MessageType::GoTop, this->world);
                //     break;
                // case ecs::MessageType::GoBottom:
                //     matchingPlayer.move(messageString, ecs::MessageType::GoBottom, this->world);
                //     break;
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

// void serverGame::Rtype::GoDirection(serverGame::Message msg, Network::MessageType dir)
// {
//     auto it = std::find_if(players.begin(), players.end(), [&msg](const Player& player) {
//         return player.getEndpoint() == msg.getEndpoint();
//     });

//     if (it != players.end()) {
//         const Player& matchingPlayer = *it;

//         serverGame::Message goRightMessage;
//         goRightMessage.setMessageType(dir);
//         goRightMessage.setMessage(matchingPlayer.getName());
//         for (auto& player : this->players) {
//             if (player.getEndpoint() != msg.getEndpoint()) {
//                 this->server.sendMessage(goRightMessage, player.getEndpoint());
//             }
//         }
//     }
// }

// void serverGame::Rtype::StopDirection(serverGame::Message msg, Network::MessageType dir)
// {
//     auto it = std::find_if(players.begin(), players.end(), [&msg](const Player& player) {
//         return player.getEndpoint() == msg.getEndpoint();
//     });

//     if (it != players.end()) {
//         const Player& matchingPlayer = *it;

//         serverGame::Message goRightMessage;
//         goRightMessage.setMessageType(dir);
//         goRightMessage.setMessage(matchingPlayer.getName());
//         for (auto& player : this->players) {
//             if (player.getEndpoint() != msg.getEndpoint()) {
//                 this->server.sendMessage(goRightMessage, player.getEndpoint());
//             }
//         }
//     }
// }

void serverGame::Rtype::sendGameState()
{
    this->mutex.lock();
    for (auto &entity : this->getEntities()) {
        if (entity.getType() == "PLAYER") {
            for (auto& newEntity : this->getEntities()) {
                if (newEntity.getType() != "TEST") {
                    std::pair<float, float> pos = newEntity.getPosition(this->world);
                    std::pair<float, float> accel = newEntity.getAcceleration(this->world);
                    std::cout << accel.first << " " << accel.second << " ";
                    std::cout << pos.first << " " << pos.second << std::endl;
                    ecs::Buffer newBuffer;
                    newBuffer.writeMessageType(ecs::MessageType::Ping);
                    std::string posStr = std::to_string(pos.first) + "," + std::to_string(pos.second);
                    newBuffer.writeString(newEntity.getType() + newEntity.getName() + posStr);
                    this->server.sendMessage(newBuffer, entity.getEndpoint());
                }
            }
        }
    }
    this->mutex.unlock();
}
void serverGame::Rtype::addMissile(serverGame::Message msg)
{
    serverGame::Message newMissileMessage;
    newMissileMessage.setMessageType(Network::MessageType::NewMissile);
    newMissileMessage.setMessage(msg.getMessage());

    for (auto& player : this->players) {
        if (player.getEndpoint() != msg.getEndpoint()) {
            this->server.sendMessage(newMissileMessage, player.getEndpoint());
        }
    }
}

