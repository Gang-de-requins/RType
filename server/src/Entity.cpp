/*
** EPITECH PROJECT, 2023
** r type
** File description:
** Server
*/

#include <iostream>
#include "EntityServer.hpp"

serverGame::EntityServer::EntityServer(std::string name, int id, ecs::World &world, ecs::Entity &entity) : _entity(entity)
{
    this->_name = name;
    static_cast<void>(id);
    static_cast<void>(world);
    this->isMovingTop = false;
    this->isMovingLeft = false;
    this->isMovingRight = false;
    this->isMovingBottom = false;
}

serverGame::EntityServer::~EntityServer()
{

}


void serverGame::EntityServer::move(ecs::MessageType msgType, ecs::World &world)
{
            ecs::Position &posSpaceship = world.get<ecs::Position>(this->_entity);
            switch (msgType) {
                case ecs::MessageType::GoTop:
                    this->isMovingTop = true;
                    posSpaceship.y += 5;
                    break;
                case ecs::MessageType::StopTop:
                    this->isMovingTop = false;
                    break;
                case ecs::MessageType::GoBottom:
                    this->isMovingBottom = true;
                    posSpaceship.y -= 5;
                    break;
                case ecs::MessageType::StopBottom:
                    this->isMovingBottom = false;
                    break;
                case ecs::MessageType::GoLeft:
                    this->isMovingLeft = true;
                    posSpaceship.x -= 5;
                    break;
                case ecs::MessageType::StopLeft:
                    this->isMovingLeft = false;
                    break;
                case ecs::MessageType::GoRight:
                    this->isMovingRight = true;
                    posSpaceship.x += 5;
                    break;
                case ecs::MessageType::StopRight:
                    this->isMovingRight = false;
                    break;
                default:
                    break;
            }
    // ecs::Acceleration &accSpaceship = world.get<ecs::Acceleration>(this->_entity);
    // std::thread stopThread;

    // std::pair<float, float> postest = this->getPosition(world);

    // std::cout << postest.first <<  " " << postest.second << std::endl;

    //char directionValue = static_cast<char>(direction);

    // switch (direction) {
    //     case ecs::MessageType::GoTop:
    //         this->isMovingTop = true;
    //         accSpaceship.ddx = 0;
    //         accSpaceship.ddy = -0.3f;
    //         accSpaceship.maxSpeed = 4.0f;
    //         break;
    //     case ecs::MessageType::GoBottom:
    //         this->isMovingBottom = true;
    //         accSpaceship.ddx = 0;
    //         accSpaceship.ddy = 0.3f;
    //         accSpaceship.maxSpeed = 4.0f;
    //         break;
    //     case ecs::MessageType::GoLeft:
    //         this->isMovingLeft = true;
    //         accSpaceship.ddx = -0.3f;
    //         accSpaceship.ddy = 0;
    //         accSpaceship.maxSpeed = 4.0f;
    //         break;
    //     case ecs::MessageType::GoRight:
    //         this->isMovingRight = true;
    //         accSpaceship.ddx = 0.3f;
    //         accSpaceship.ddy = 0;
    //         accSpaceship.maxSpeed = 4.0f;
    //         break;
    //     case ecs::MessageType::StopTop:
    //         this->isMovingTop = false;
    //         stopThread = std::thread(&Entity::stopMoving, this, std::ref(accSpaceship));
    //         stopThread.detach();
    //         break;
    //     case ecs::MessageType::StopBottom:
    //         this->isMovingBottom = false;
    //         stopThread = std::thread(&Entity::stopMoving, this, std::ref(accSpaceship));
    //         stopThread.detach();
    //         break;
    //     case ecs::MessageType::StopLeft:
    //         this->isMovingLeft = false;
    //         stopThread = std::thread(&Entity::stopMoving, this, std::ref(accSpaceship));
    //         stopThread.detach();
    //         break;
    //     case ecs::MessageType::StopRight:
    //         this->isMovingRight = false;
    //         stopThread = std::thread(&Entity::stopMoving, this, std::ref(accSpaceship));
    //         stopThread.detach();
    //         break;
    //     default:
    //         break;
    // }

}

void serverGame::EntityServer::stopMoving(ecs::Acceleration &accSpaceship)
{
    std::mutex mutex;
    while (!this->isMovingTop && !this->isMovingBottom && !this->isMovingLeft && !this->isMovingRight) {
        std::unique_lock<std::mutex> lock(mutex);
        accSpaceship.ddx *= -1;
        accSpaceship.ddy *= -1;
        accSpaceship.maxSpeed -= 0.1f;
        accSpaceship.maxSpeed = std::max(accSpaceship.maxSpeed, 0.0f);
        lock.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(15));
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