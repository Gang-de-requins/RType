#ifndef MESSAGE_TYPE_HPP
#define MESSAGE_TYPE_HPP

namespace server {
    enum class MessageType : char {
        PLAYER_CONNECTED = 0x01,
        PLAYER_DISCONNECTED = 0x02,
        PLAYER_MOVE = 0x03,
        PLAYER_SHOOT = 0x04,
        ENEMY_SPAWN = 0x05,
    };
}

#endif /* MESSAGE_TYPE_HPP */
