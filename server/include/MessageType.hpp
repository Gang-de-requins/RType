#ifndef MESSAGE_TYPE_HPP
#define MESSAGE_TYPE_HPP

namespace server {
    enum class MessageType : char {
        PLAYER_CONNECTED = 0x01,
        PLAYER_DISCONNECTED = 0x02,

    };
}

#endif /* MESSAGE_TYPE_HPP */
