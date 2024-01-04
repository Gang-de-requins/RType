/*
** EPITECH PROJECT, 2023
** r type
** File description:
** Server
*/

#include <cstdlib>

#include <iostream>
#include "Rtype.hpp"
#include "Network.hpp"

serverGame::Rtype::Rtype(int port)
{
    this->server.setupServer(port);
    this->id = 0;
    this->nbEnemiesToSpawn = 4;
    this->nbEnemiesSpawned = 0;

    ecs::Scene &game = this->world.createScene();
}

serverGame::Rtype::~Rtype()
{

}

void serverGame::Rtype::run(void)
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    while(true)
    {
        this->world.update();

        processMessages();

        // std::cout << "Nb players: " << this->players.size() << std::endl;
        // std::cout << "Nb enemies: " << this->nbEnemiesSpawned << std::endl;

        if (this->nbEnemiesSpawned == 0 && this->players.size() >= 2) {
            for (int i = 0; i < this->nbEnemiesToSpawn; i++) {
                int randomY = std::rand() % 1080;

                serverGame::Message existingPlayerMessage;
                existingPlayerMessage.setMessageType(Network::MessageType::NewEnemy);
                std::string position = "Position:" + std::to_string(randomY) + "," + std::to_string(0);
                existingPlayerMessage.setMessage(position);

                for (auto& player : this->players) {
                    if (player.getId() != 0) {
                        this->server.sendMessage(existingPlayerMessage, player.getEndpoint());
                    }
                }

                this->nbEnemiesSpawned++;

                ecs::Scene &game = this->world.getCurrentScene();
                ecs::Entity &enemy = this->world.createEntity(game);
                world.assign(enemy, ecs::Position{static_cast<float>(0), static_cast<float>(randomY)});
                world.assign(enemy, ecs::Name{"enemy", ecs::Position{-20, -20}});
            }
        }
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
        if (msg.getMessageType() == Network::MessageType::NewMissile)
            addMissile(msg);
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

        if (msg.getMessageType() == Network::MessageType::EnemyDead)
            EnemyDead(msg);
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
            this->server.sendMessage(goRightMessage, player.getEndpoint());
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
            this->server.sendMessage(goRightMessage, player.getEndpoint());
        }
    }
}

void serverGame::Rtype::addPlayer(serverGame::Message msg)
{
    std::cout << "Add player" << std::endl;
    this->id++;
    Player newPlayer(msg.getMessage(), this->id, this->world);
    newPlayer.setEndpoint(msg.getEndpoint());
    players.push_back(newPlayer);

    float randomX = std::rand() % 800;
    float randomY = std::rand() % 450;

    ecs::Scene &game = this->world.getCurrentScene();
    ecs::Entity &player = this->world.createEntity(game);
    world.assign(player, ecs::Position{randomX, randomY});
    world.assign(player, ecs::Name{newPlayer.getName(), ecs::Position{-20, -20}});
    world.assign(player, ecs::Controllable{KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE, 0.05, std::chrono::steady_clock::now()});

    serverGame::Message playerJoinMessage;
    playerJoinMessage.setMessageType(Network::MessageType::PlayerJoin);
    playerJoinMessage.setMessage(newPlayer.getName() + "|" + std::to_string(randomX) + "," + std::to_string(randomY));

    std::vector<ecs::Entity *> entities = this->world.getSceneManager().view<ecs::Controllable>(game);
    int i = 0;
    for (auto& player : this->players) {
        auto &pos = this->world.get<ecs::Position>(*entities[i]);

        std::string playerNameMessage = player.getName() + "|" + std::to_string(pos.x) + "," + std::to_string(pos.y);
        serverGame::Message existingPlayerMessage;
        existingPlayerMessage.setMessageType(Network::MessageType::PlayerJoin);
        existingPlayerMessage.setMessage(playerNameMessage);

        this->server.sendMessage(playerJoinMessage, player.getEndpoint());
        if (newPlayer.getId() != player.getId())
            this->server.sendMessage(existingPlayerMessage, newPlayer.getEndpoint());

        i++;
    }
}

void serverGame::Rtype::addMissile(serverGame::Message msg)
{
    serverGame::Message newMissileMessage;
    newMissileMessage.setMessageType(Network::MessageType::NewMissile);
    newMissileMessage.setMessage(msg.getMessage());

    ecs::Scene &game = this->world.getCurrentScene();
    ecs::Entity &Shoot = world.createEntity(game);

    for (auto& player : this->players) {
        this->server.sendMessage(newMissileMessage, player.getEndpoint());
    }
}

void serverGame::Rtype::EnemyDead(serverGame::Message msg)
{
    serverGame::Message deadMessage;
    deadMessage.setMessageType(Network::MessageType::EnemyDead);
    deadMessage.setMessage(msg.getMessage());

    //ecs::Entity entity = this->world.getSceneManager().getEntityById(this->world.getCurrentScene(), std::stoi(msg.getMessage()));

    for (auto& player : this->players) {
        this->server.sendMessage(deadMessage, player.getEndpoint());
    }
}

