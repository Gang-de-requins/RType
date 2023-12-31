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
        GoRight = 0x05,
        GoLeft = 0x06,
        GoTop = 0x07,
        GoBottom = 0x08,
        StopRight = 0x09,
        StopLeft = 0x10,
        StopTop = 0x11,
        StopBottom = 0x12,
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
            void setRunning(bool running);
        
        private:
            void newPlayerConnected(Game &game, std::string name);
            void moveEntity(Game &game, std::string name, ::Network::MessageType type);
    };
}

#endif /* GAME_NETWORK_HPP */
