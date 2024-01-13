/*
** EPITECH PROJECT, 2023
** r type
** File description:
** Server
*/

#include <iostream>
#include "Rtype.hpp"
#include "Network.hpp"

serverGame::Rtype::Rtype(int port)
{
    this->server.setupServer(port);
    this->id = 0;
    this->test = 0;
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
            
            // serverGame::Message existingPlayerMessage;
            // existingPlayerMessage.setMessageType(Network::MessageType::NewEnemy);
            // existingPlayerMessage.setMessage("Position:800,800");

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
    while (!this->messageList.empty())
    {
        this->mutex.lock();
        ecs::Message message = this->messageList.front();
        this->messageList.erase(this->messageList.begin());
        this->mutex.unlock();

        ecs::MessageType messageType = message.getMessageType();

        switch (messageType) {
            case ecs::MessageType::PlayerJoined: {
                ecs::PlayerJoined receivedStruct;
                receivedStruct.deserialize(message.getMessageData());
                std::cout << "Received PlayerJoinRequest: playername = " << receivedStruct.playername << std::endl;
                addPlayer(receivedStruct.playername, message.getEndpoint());
                break;
            }
            case ecs::MessageType::NewMissile: {
                for (auto& entity : this->getEntities()) {
                    if (entity->getEndpoint() == message.getEndpoint()) {
                        std::string tt = std::to_string(this->test);
                        this->test++;
                    }
                }
                break;
            }
            case ecs::MessageType::Move: {
                ecs::Move receivedStruct;
                receivedStruct.deserialize(message.getMessageData());
                for (auto& entity : this->getEntities()) {
                    if (entity->getEndpoint() == message.getEndpoint())
                        entity->move(receivedStruct.direction, this->world);
                }
                break;
            }
            default:
                std::cout << "Unknown message type received: " << static_cast<int>(message.getMessageType()) << std::endl;
                break;
        }
    }
}

void serverGame::Rtype::addDefault(std::string name)
{
    ecs::Scene &inGame = world.getCurrentScene();
    ecs::Entity &entity = world.createEntity(inGame);

    world.assign(entity, ecs::Position{200, 200});
    world.assign(entity, ecs::Health{100});
    world.assign(entity, ecs::Velocity{0, 0});
    world.assign(entity, ecs::Sprite{"assets/characters.gif", ecs::Rectangle{0, 0, 32, 16}, ecs::Vector2{0, 0}});
    world.assign(entity, ecs::Acceleration{0, 0, 4});
    world.assign(entity, ecs::Scale{1, 1});
    world.assign(entity, ecs::Rotation{0});
    world.assign(entity, ecs::Name{name, ecs::Position{-20, -20}});

   auto newEntity = std::make_shared<serverGame::EntityServer>(name, this->id, this->world, entity);
    newEntity->setType("TEST");
    this->mutex.lock();
    this->entities.push_back(newEntity);
    this->mutex.unlock();
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
    world.assign(entity, ecs::Name{name, ecs::Position{-20, -20}});

    auto newEntity = std::make_shared<serverGame::EntityServer>(name, this->id, this->world, entity);
    newEntity->setEndpoint(endpoint);
    newEntity->setType("PLAYER");
    this->mutex.lock();
    this->entities.push_back(newEntity);
    this->mutex.unlock();

    ecs::NewPlayer newPlayer = {name, entity.id, {200, 200}, 100};
    this->server.send(newPlayer, ecs::MessageType::PlayerJoinedAccept, newEntity->getEndpoint());


    for (auto& entity : this->entities) {
        if (entity->getType() != "TEST") {
            if (entity->getName() != newEntity->getName()) {
                ecs::NewPlayer existingPlayer = {entity->getName(), 0, {0, 0}, 100};
                this->server.send(existingPlayer, ecs::MessageType::NewPlayer, newEntity->getEndpoint());
                this->server.send(newPlayer, ecs::MessageType::NewPlayer, entity->getEndpoint());
            }
        }
    }
}


void serverGame::Rtype::addMissile(std::string name)
{
    ecs::Scene &inGame = world.getCurrentScene();
    ecs::Entity &entity = world.createEntity(inGame);

    world.assign(entity, ecs::Position{200, 200});
    world.assign(entity, ecs::Velocity{3, 0});
    world.assign(entity, ecs::Sprite{"assets/characters.gif", ecs::Rectangle{0, 0, 32, 16}, ecs::Vector2{0, 0}});
    world.assign(entity, ecs::Acceleration{0, 0, 4});
    world.assign(entity, ecs::Scale{1, 1});
    world.assign(entity, ecs::Rotation{0});
    world.assign(entity, ecs::Name{name, ecs::Position{-20, -20}});

   auto newEntity = std::make_shared<serverGame::EntityServer>(name, this->id, this->world, entity);
    newEntity->setType("TEST");
    this->mutex.lock();
    this->entities.push_back(newEntity);
    this->mutex.unlock();
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
    ecs::EntityList entityList;
    for (auto &entity : this->getEntities()) {
        if (entity->getType() != "TEST") {
            std::pair<float, float> pos = entity->getPosition(this->world);
            ecs::EntityInfo entityInfo;
            entityInfo.playername = entity->getName();
            entityInfo.id = entity->getEntity().id;
            entityInfo.hp = entity->getHealth(this->world);
            entityInfo.pos = pos;
            entityList.entityList.push_back(entityInfo);
        }
    }
    
    for (auto &entity : this->getEntities()) {
        if (entity->getType() == "PLAYER")
            this->server.send(entityList, ecs::MessageType::EntityList, entity->getEndpoint());
    }
    this->mutex.unlock();
}

// void serverGame::Rtype::addMissile(serverGame::Message msg)
// {
//     serverGame::Message newMissileMessage;
//     newMissileMessage.setMessageType(Network::MessageType::NewMissile);
//     newMissileMessage.setMessage(msg.getMessage());

//     // for (auto& player : this->players) {
//     //     if (player.getEndpoint() != msg.getEndpoint()) {
//     //         this->server.sendMessage(newMissileMessage, player.getEndpoint());
//     //     }
//     // }
// }

