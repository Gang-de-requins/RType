/*
** EPITECH PROJECT, 2023
** r type
** File description:
** Server
*/

#include <iostream>
#include <boost/asio.hpp>
#include "Entity.hpp"

serverGame::Entity::Entity(std::string name, int id, ecs::World &world) : _entity(world.createEntity(world.getCurrentScene()))
{
    ecs::Scene &inGame = world.getCurrentScene();
    this->_entity = world.createEntity(inGame);
    this->_name = name;

    world.assign(this->_entity, ecs::Position{200, 200});
    world.assign(this->_entity, ecs::Health{100});
    world.assign(this->_entity, ecs::Velocity{0, 0});
    world.assign(this->_entity, ecs::Sprite{"assets/characters.gif", ecs::Rectangle{0, 0, 32, 16}, ecs::Vector2{0, 0}});
    world.assign(this->_entity, ecs::Acceleration{0, 0, 4});
    world.assign(this->_entity, ecs::Scale{1, 1});
    world.assign(this->_entity, ecs::Rotation{0});
    world.assign(this->_entity, ecs::Controllable{KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT});
    world.assign(this->_entity, ecs::Collision{false, {}});
    world.assign(this->_entity, ecs::Animation{ecs::Rectangle{0, 0, 32, 0}, 4, 0, 300, std::chrono::steady_clock::now()});
    world.assign(this->_entity, ecs::Name{name, ecs::Position{-20, -20}});
    this->isMovingTop = false;
    this->isMovingLeft = false;
    this->isMovingRight = false;
    this->isMovingBottom = false;
}

serverGame::Entity::~Entity()
{

}


void serverGame::Entity::move(std::string name, Network::MessageType direction, ecs::World &world)
{
    ecs::Acceleration &accSpaceship = world.get<ecs::Acceleration>(this->_entity);
    std::thread stopThread;

    std::pair<float, float> postest = this->getPosition(world);

    std::cout << postest.first <<  " " << postest.second << std::endl;

    char directionValue = static_cast<char>(direction);

    switch (direction) {
        case ::Network::MessageType::GoTop:
            this->isMovingTop = true;
            accSpaceship.ddx = 0;
            accSpaceship.ddy = -0.3f;
            accSpaceship.maxSpeed = 4.0f;
            break;
        case ::Network::MessageType::GoBottom:
            this->isMovingBottom = true;
            accSpaceship.ddx = 0;
            accSpaceship.ddy = 0.3f;
            accSpaceship.maxSpeed = 4.0f;
            break;
        case ::Network::MessageType::GoLeft:
            this->isMovingLeft = true;
            accSpaceship.ddx = -0.3f;
            accSpaceship.ddy = 0;
            accSpaceship.maxSpeed = 4.0f;
            break;
        case ::Network::MessageType::GoRight:
            std::cout << "HEREE" << std::endl;
            this->isMovingRight = true;
            accSpaceship.ddx = 0.3f;
            accSpaceship.ddy = 0;
            accSpaceship.maxSpeed = 4.0f;
            break;
        case ::Network::MessageType::StopTop:
            this->isMovingTop = false;
            stopThread = std::thread(&Entity::stopMoving, this, std::ref(accSpaceship));
            stopThread.detach();
            break;
        case ::Network::MessageType::StopBottom:
            this->isMovingBottom = false;
            stopThread = std::thread(&Entity::stopMoving, this, std::ref(accSpaceship));
            stopThread.detach();
            break;
        case ::Network::MessageType::StopLeft:
            this->isMovingLeft = false;
            stopThread = std::thread(&Entity::stopMoving, this, std::ref(accSpaceship));
            stopThread.detach();
            break;
        case ::Network::MessageType::StopRight:
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