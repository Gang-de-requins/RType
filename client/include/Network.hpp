#ifndef GAME_NETWORK_HPP
#define GAME_NETWORK_HPP

#include <iostream>
#include <thread>
#include <utility>
#include <boost/asio.hpp>

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

namespace ecs {
    class World;
}

namespace rtype {
    class Game;

    class Network {
        boost::asio::io_context m_ioContext;
        boost::asio::ip::udp::socket m_socket;
        boost::asio::ip::udp::endpoint m_endpoint;
        std::vector<std::thread> m_threads;

        bool m_running;

        public:
            Network();
            ~Network();
            void connect(std::string ip, int port, Game &game);
            void send(::Network::MessageType type, std::string message);
            void receive(Game &game);

            void newPlayerConnected(Game &game, std::string name);

            void setRunning(bool running);
    };
}

#endif /* GAME_NETWORK_HPP */
