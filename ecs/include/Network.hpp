#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <string>

namespace ecs {
    enum class MessageType : char {
        // PlayerJoin = 0x01,
        // PlayerJoinResponse = 0x02,
        // PlayerAction = 0x03,
        // NewPlayer = 0x04,
        // GoRight = 0x05,
        // GoLeft = 0x06,
        // GoTop = 0x07,
        // GoBottom = 0x08,
        // StopRight = 0x09,
        // StopLeft = 0x10,
        // StopTop = 0x11,
        // StopBottom = 0x12,
        // Ping = 0x13,
        PLAYER_CONNECTED = 0x01,
        PLAYER_DISCONNECTED = 0x02,
        PLAYER_MOVE = 0x03,
        PLAYER_SHOOT = 0x04,
        ENEMY_SPAWN = 0x05,
        ENEMY_SHOOT = 0x06,
        ENTITY_DESTROYED = 0x07,
    };

    enum class PlayerActionType : char {
        MoveLeft = 0x01,
        MoveRight = 0x02,
        Shoot = 0x03,
    };

    struct PlayerJoin {
        MessageType type;
        std::string playerName;
    };

    struct PlayerJoinResponse {
        MessageType type;
        int playerId;
        bool success;
    };

    struct PlayerAction {
        MessageType type;
        int playerId;
        PlayerActionType actionType;
    };
};

#endif /* NETWORK_HPP */
