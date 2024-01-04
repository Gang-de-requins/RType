/*
** EPITECH PROJECT, 2023
** r type
** File description:
** Server
*/

#ifndef MESSAGE_HPP_
#define MESSAGE_HPP_

#include <iostream>
#include <boost/asio.hpp>
#include "Network.hpp"

namespace serverGame
{
    class Message
    {
    public:
        Message();
        ~Message();
        void setMessageType(Network::MessageType messageType)
        {
            this->_messageType = messageType;
        }

        void setMessage(std::string msg)
        {
            this->_msg = msg;
        }

        Network::MessageType getMessageType() const
        {
            return this->_messageType;
        }

        std::string getMessage() const
        {
            return this->_msg;
        }

        void setEndpoint(boost::asio::ip::udp::endpoint endpoint)
        {
            this->_endpoint = endpoint;
        }

        boost::asio::ip::udp::endpoint getEndpoint()
        {
            return this->_endpoint;
        }


    private:
        Network::MessageType _messageType;
        std::string _msg;
        boost::asio::ip::udp::endpoint _endpoint;
    };
}

#endif /* !MESSAGE_HPP_ */
