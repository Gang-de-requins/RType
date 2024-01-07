/*
** EPITECH PROJECT, 2023
** r type
** File description:
** Server
*/

#include <iostream>
#include "EntityServer.hpp"

serverGame::Entity::Entity(std::string name, int id, ecs::World &world, ecs::Entity &entity) : _entity(entity)
{
    this->_name = name;
    static_cast<void>(id);
    static_cast<void>(world);
    // ecs::Scene &inGame = world.getCurrentScene();
    // this->_entity = world.createEntity(inGame);

    // world.assign(this->_entity, ecs::Position{200, 200});
    // world.assign(this->_entity, ecs::Health{100});
    // world.assign(this->_entity, ecs::Velocity{0, 0});
    // world.assign(this->_entity, ecs::Sprite{"assets/characters.gif", ecs::Rectangle{0, 0, 32, 16}, ecs::Vector2{0, 0}});
    // world.assign(this->_entity, ecs::Acceleration{0, 0, 4});
    // world.assign(this->_entity, ecs::Scale{1, 1});
    // world.assign(this->_entity, ecs::Rotation{0});
    // world.assign(this->_entity, ecs::Controllable{KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT});
    // world.assign(this->_entity, ecs::Collision{false, {}});
    // world.assign(this->_entity, ecs::Animation{ecs::Rectangle{0, 0, 32, 0}, 4, 0, 300, std::chrono::steady_clock::now()});
    // world.assign(this->_entity, ecs::Name{name, ecs::Position{-20, -20}});
    this->isMovingTop = false;
    this->isMovingLeft = false;
    this->isMovingRight = false;
    this->isMovingBottom = false;
}

serverGame::Entity::~Entity()
{

}


void serverGame::Entity::move(std::string name, ecs::MessageType direction, ecs::World &world)
{
    static_cast<void>(name);
    ecs::Acceleration &accSpaceship = world.get<ecs::Acceleration>(this->_entity);
    std::thread stopThread;

    std::pair<float, float> postest = this->getPosition(world);

    std::cout << postest.first <<  " " << postest.second << std::endl;

    //char directionValue = static_cast<char>(direction);

    switch (direction) {
        case ecs::MessageType::GoTop:
            this->isMovingTop = true;
            accSpaceship.ddx = 0;
            accSpaceship.ddy = -0.3f;
            accSpaceship.maxSpeed = 4.0f;
            break;
        case ecs::MessageType::GoBottom:
            this->isMovingBottom = true;
            accSpaceship.ddx = 0;
            accSpaceship.ddy = 0.3f;
            accSpaceship.maxSpeed = 4.0f;
            break;
        case ecs::MessageType::GoLeft:
            this->isMovingLeft = true;
            accSpaceship.ddx = -0.3f;
            accSpaceship.ddy = 0;
            accSpaceship.maxSpeed = 4.0f;
            break;
        case ecs::MessageType::GoRight:
            this->isMovingRight = true;
            accSpaceship.ddx = 0.3f;
            accSpaceship.ddy = 0;
            accSpaceship.maxSpeed = 4.0f;
            break;
        case ecs::MessageType::StopTop:
            this->isMovingTop = false;
            stopThread = std::thread(&Entity::stopMoving, this, std::ref(accSpaceship));
            stopThread.detach();
            break;
        case ecs::MessageType::StopBottom:
            this->isMovingBottom = false;
            stopThread = std::thread(&Entity::stopMoving, this, std::ref(accSpaceship));
            stopThread.detach();
            break;
        case ecs::MessageType::StopLeft:
            this->isMovingLeft = false;
            stopThread = std::thread(&Entity::stopMoving, this, std::ref(accSpaceship));
            stopThread.detach();
            break;
        case ecs::MessageType::StopRight:
            this->isMovingRight = false;
            stopThread = std::thread(&Entity::stopMoving, this, std::ref(accSpaceship));
            stopThread.detach();
            break;
        default:
            break;
    }

}

void serverGame::Entity::stopMoving(ecs::Acceleration &accSpaceship)
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

std::pair<float, float> serverGame::Entity::getPosition(ecs::World &world)
{
    ecs::Position &test = world.get<ecs::Position>(this->_entity);
    std::pair<float, float> pos;

    pos.first = test.x;
    pos.second = test.y;

    return pos;
}

std::pair<float, float> serverGame::Entity::getAcceleration(ecs::World &world)
{
    ecs::Acceleration &test = world.get<ecs::Acceleration>(this->_entity);
    std::pair<float, float> accel;

    accel.first = test.ddx;
    accel.second = test.ddy;

    return accel;
}