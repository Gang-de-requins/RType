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
            void setMessageType(MessageType messageType)
            {
                this->_messageType = messageType;
            }
            void setMessage(std::string msg)
            {
                this->_msg = msg;
            }

        private:
            MessageType _messageType;
            std::string _msg;
    };
}

#endif /* MESSAGE_HPP */
