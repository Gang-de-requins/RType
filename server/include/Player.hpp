/*
** EPITECH PROJECT, 2023
** r type
** File description:
** Server
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <iostream>
#include <boost/asio.hpp>
#include "GameEngine.hpp"

namespace serverGame
{
    class Player : public ecs::Entity
    {
    public:
        Player(std::string name, int id, ecs::World &world);
        ~Player();
        void setName(std::string name)
        {
            this->_name = name;
        }

        std::string getName() const
        {
            return this->_name;
        }

        int getId() const
        {
            return this->_id;
        }

        void setEndpoint(boost::asio::ip::udp::endpoint endpoint)
        {
            this->_endpoint = endpoint;
        }

        boost::asio::ip::udp::endpoint getEndpoint() const
        {
            return this->_endpoint;
        }


    private:
        ecs::Entity entity;
        int _id;
        std::string _name;
        boost::asio::ip::udp::endpoint _endpoint;
    };
}

#endif /* !PLAYER_HPP_ */
