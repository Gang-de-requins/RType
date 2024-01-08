/*
** EPITECH PROJECT, 2023
** r type
** File description:
** Server
*/

#include <iostream>
#include "Player.hpp"

serverGame::Player::Player(std::string name, int id, ecs::World &world)
{
    ecs::Scene &inGame = world.createScene();
    world.createEntity(inGame);

    // this->entityChar = world.createEntity(inGame);
    // ecs::Position position{200, 200};
    // ecs::Velocity velocity{0, 0};
    // ecs::Acceleration acceleration{0, 0, 4};
    // ecs::Scale scale{1, 1};
    // ecs::Rotation rotation{0};

    // world.assign(this->entityChar, position);
    // world.assign(this->entityChar, velocity);
    // world.assign(this->entityChar, acceleration);
    // world.assign(this->entityChar, scale);
    // world.assign(this->entityChar, rotation);

    // this->entityName = world.createEntity(inGame);
    // ecs::Position position1{180, 180};
    // ecs::Velocity velocity1{0, 0};
    // ecs::Text text{name};
    // ecs::Acceleration acceleration1{0, 0, 4};
    // ecs::Color color{GE_WHITE};
    // ecs::FontSize fontSize{ 20 };

    // world.assign(this->entityName, position1);
    // world.assign(this->entityName, velocity1);
    // world.assign(this->entityName, text);
    // world.assign(this->entityName, acceleration1);
    // world.assign(this->entityName, color);
    // world.assign(this->entityName, fontSize);

    this->_id = id;
    this->_name = name;
}

serverGame::Player::~Player()
{

}


