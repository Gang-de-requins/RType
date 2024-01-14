#ifndef GAME_NETWORK_HPP
#define GAME_NETWORK_HPP

#include <iostream>
#include <thread>
#include <utility>
#if defined(_WIN32)           
    #define NOGDI
    #define NOUSER
#endif

#include <asio.hpp>
#include <GameEngine.hpp>

#if defined(_WIN32)
    #undef near
    #undef far
#endif

namespace ecs {
    class World;
}

namespace rtype {
    class Game;

    class Network {
        asio::io_context m_ioContext;
        asio::ip::udp::socket m_socket;
        asio::ip::udp::endpoint m_endpoint;
        std::vector<std::thread> m_threads;

        bool m_running;
        bool m_connected;

        public:
            std::string m_ip;
            unsigned short m_port;
            Network();
            ~Network();
            template <typename T>
            void send(T& data, ecs::MessageType messageType);

            void connect(const std::string &ip, const unsigned short port, Game &game, const std::string &playerName);
            void receive(Game &game);
            void setRunning(bool running);
            bool isConnected() const;
        
        private:
            void newPlayerConnected(Game &game, ecs::NewPlayer &newPlayer, bool isMe);
            void playerDisconnected(Game &game, std::string msg);
            //void moveEntity(Game &game, std::string name, ::Network::MessageType type);
            void moveEntity(Game &game, std::string msg);
            void newMissile(Game &game, std::string msg);
            void newEnemy(Game &game, std::string msg);
            void newEnemy(Game &game, ecs::NewPlayer& newPlayer);
    };
}

#endif /* GAME_NETWORK_HPP */
