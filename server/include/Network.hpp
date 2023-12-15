/*
** EPITECH PROJECT, 2023
** r type
** File description:
** Server
*/

#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include <iostream>
#include <vector>
#include <cstring>


namespace Network
{
    enum class MessageType : char {
        PlayerJoin = 0x01,
        PlayerJoinResponse = 0x02,
        PlayerAction = 0x03,
        NewPlayer = 0x04,
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
}
#endif /* !NETWORK_HPP_ */
