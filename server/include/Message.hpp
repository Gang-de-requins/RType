#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>
#include <asio.hpp>
#include "MessageType.hpp"

namespace server {
    class Message {
        public:
            Message() {}
            ~Message() {}

        private:
            MessageType _messageType;
            std::string _msg;
    };
}

#endif /* MESSAGE_HPP */
