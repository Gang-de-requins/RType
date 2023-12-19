/*
** EPITECH PROJECT, 2023
** r type
** File description:
** Server
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <iostream>
#include <boost/asio.hpp>
#include "GameEngine.hpp"
#include "Network.hpp"
#include <thread>
#include <chrono>
#include <utility>

namespace serverGame
{
    class Entity
    {

    public:
        Entity(std::string name, int id, ecs::World &world);
        ~Entity();
        void setName(std::string name)
        {
            this->_name = name;
        }

        std::string getName() const
        {
            return this->_name;
        }

        void setEndpoint(boost::asio::ip::udp::endpoint endpoint)
        {
            this->_endpoint = endpoint;
        }

        void setType(std::string type)
        {
            this->_type = type;
        }

        boost::asio::ip::udp::endpoint getEndpoint() const
        {
            return this->_endpoint;
        }

        std::string getType() const
        {
            return this->_type;
        }

        void move(std::string name, Network::MessageType direction, ecs::World &world);
        void stopMoving(ecs::Acceleration &accSpaceship);
        std::pair<float, float> getPosition(ecs::World &world);
        bool isMovingTop;
        bool isMovingLeft;
        bool isMovingRight;
        bool isMovingBottom;

    private:
        ecs::Entity _entity;
        std::string _type;
        std::string _name;
        boost::asio::ip::udp::endpoint _endpoint;
        int _hp;
    };
}

#endif /* !ENTITY_HPP_ */
