/*
** EPITECH PROJECT, 2023
** r type
** File description:
** Server
*/

#include <iostream>
#include <boost/asio.hpp>
#include "Player.hpp"

serverGame::Player::Player(std::string name, int id, ecs::World &world)
{
    this->_id = id;
    this->_name = name;
}

serverGame::Player::~Player()
{

}


