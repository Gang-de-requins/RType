/*
** EPITECH PROJECT, 2023
** r type
** File description:
** Server
*/

#include <iostream>
#include <thread>
#include <mutex>
#include "EntityServer.hpp"

namespace serverGame {

EntityServer::EntityServer(std::string name, int id, ecs::World &world, ecs::Entity &entity) 
: _entity(entity), isMovingTop(false), isMovingLeft(false), isMovingRight(false), isMovingBottom(false), isMoving(false) {
    this->_name = name;
    static_cast<void>(id);
    static_cast<void>(world);
}

EntityServer::~EntityServer() {
    if (isMoving) {
        isMoving = false;
        if (moveThread.joinable()) {
            moveThread.join();
        }
    }
}

void EntityServer::move(ecs::MessageType msgType, ecs::World &world) {
    switch (msgType) {
        case ecs::MessageType::GoTop:
            isMovingTop = true;
            break;
        case ecs::MessageType::StopTop:
            isMovingTop = false;
            break;
        case ecs::MessageType::GoBottom:
            isMovingBottom = true;
            break;
        case ecs::MessageType::StopBottom:
            isMovingBottom = false;
            break;
         case ecs::MessageType::GoLeft:
            isMovingLeft = true;
            break;
        case ecs::MessageType::StopLeft:
            isMovingLeft = false;
            break;
        case ecs::MessageType::GoRight:
            isMovingRight = true;
            break;
        case ecs::MessageType::StopRight:
            isMovingRight = false;
            break;
        default:
            break;
    }

    if (!isMoving) {
        isMoving = true;
        this->moveThread = std::thread(&EntityServer::moveEntity, this, std::ref(world));
    }
}


void EntityServer::moveEntity(ecs::World &world) {
    while (isMoving) {
        int deltaX = 0, deltaY = 0;
        if (isMovingLeft) deltaX -= 15;
        if (isMovingRight) deltaX += 15;
        if (isMovingTop) deltaY -= 15;
        if (isMovingBottom) deltaY += 15;

        {
            std::lock_guard<std::mutex> lock(posMutex);
            ecs::Position &posSpaceship = world.get<ecs::Position>(this->_entity);
            posSpaceship.x += deltaX;
            posSpaceship.y += deltaY;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Adjust movement rate as needed
    }
}


void EntityServer::stopMoving() {
    isMoving = false;
    if (moveThread.joinable()) {
        moveThread.join();
    }
}

std::pair<float, float> serverGame::EntityServer::getPosition(ecs::World &world)
{
    ecs::Position &test = world.get<ecs::Position>(this->_entity);
    std::pair<float, float> pos;
    pos.first = test.x;
    pos.second = test.y;

    return pos;
}

float serverGame::EntityServer::getHealth(ecs::World &world)
{
    ecs::Health &test = world.get<ecs::Health>(this->_entity);
    return test.health;
}

std::pair<float, float> serverGame::EntityServer::getAcceleration(ecs::World &world)
{
    ecs::Acceleration &test = world.get<ecs::Acceleration>(this->_entity);
    std::pair<float, float> accel;

    accel.first = test.ddx;
    accel.second = test.ddy;

    return accel;
}
}