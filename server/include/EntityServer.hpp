/*
** EPITECH PROJECT, 2023
** r type
** File description:
** Server
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <iostream>
#if defined(_WIN32)
    #define NOGDI
    #define NOUSER
#endif

#include <boost/asio.hpp>

#if defined(_WIN32)
    #undef near
    #undef far
#endif
#include <thread>
#include <chrono>
#include <utility>
#include "Network.hpp"
#include "GameEngine.hpp"

namespace serverGame
{
    class EntityServer
    {

    public:
        EntityServer(std::string name, int id, ecs::World &world, ecs::Entity &entity);
        ~EntityServer();
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

        ecs::Entity& getEntity() const {
            return _entity;
        }

        void move(ecs::MessageType direction, ecs::World &world);
        void stopMoving(ecs::Acceleration &accSpaceship);
        void continuousMovement(ecs::Acceleration &accSpaceship, ecs::MessageType direction);
        std::pair<float, float> getPosition(ecs::World &world);
        std::pair<float, float> getAcceleration(ecs::World &world);
        float getHealth(ecs::World &world);
        bool isMovingTop;
        bool isMovingLeft;
        bool isMovingRight;
        bool isMovingBottom;

    private:
        ecs::Entity &_entity;
        std::string _type;
        std::string _name;
        boost::asio::ip::udp::endpoint _endpoint;
        int _hp;
    };
}

#endif /* !ENTITY_HPP_ */
