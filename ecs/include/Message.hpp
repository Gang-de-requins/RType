#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <iostream>
#include <fstream>
#include <string_view>
#include <vector>
#include <array>
#include <cctype>
#include <algorithm>
#if defined(_WIN32)
#define NOGDI
#define NOUSER
#endif

#include <asio.hpp>

#if defined(_WIN32)
#undef near
#undef far
#endif
#include "rapidjson/document.h"
#include "Macros.hpp"
#include "Network.hpp"
#include "components/Components.hpp"

namespace ecs {
    class Message {
        public:
        Message() {
        }

        ~Message() {
        }

        void setMessageType(ecs::MessageType messageType)
        {
            this->_messageType = messageType;
        }

        ecs::MessageType getMessageType() const
        {
            return this->_messageType;
        }

        void setEndpoint(asio::ip::udp::endpoint endpoint)
        {
            this->_endpoint = endpoint;
        }

        asio::ip::udp::endpoint getEndpoint()
        {
            return this->_endpoint;
        }

        void setMessageData(const std::vector<char>& messageData)
        {
            this->_messageData = messageData;
        }

        const std::vector<char> &getMessageData() const
        {
            return this->_messageData;
        }

    private:
        ecs::MessageType _messageType;
        std::vector<char> _messageData;
        asio::ip::udp::endpoint _endpoint;
    };
};

#endif /* MESSAGE_HPP */
