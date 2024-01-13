#ifndef GAME_NETWORK_HPP
#define GAME_NETWORK_HPP

#include <iostream>
#include <thread>
#include <utility>
#if defined(_WIN32)           
    #define NOGDI
    #define NOUSER
#endif

#include <boost/asio.hpp>
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
        boost::asio::io_context m_ioContext;
        boost::asio::ip::udp::socket m_socket;
        boost::asio::ip::udp::endpoint m_endpoint;
        std::vector<std::thread> m_threads;

        bool m_running;

        public:
            std::string m_ip;
            unsigned short m_port;
            Network();
            ~Network();
            void connect(std::string ip, int port, Game &game);
            //void send(::Network::MessageType type, std::string message);
            //void send(ecs::MessageType type, std::string message);

            template <typename T>
            void send(T& data, ecs::MessageType messageType);
            void connect(const std::string &ip, const unsigned short port, Game &game, const std::string &playerName);
            //void send(::Network::MessageType type, std::string message);
            void receive(Game &game);
            void setRunning(bool running);
        
        private:
            void newPlayerConnected(Game &game, std::string name);
            //void moveEntity(Game &game, std::string name, ::Network::MessageType type);
            void moveEntity(Game &game, std::string name, std::pair<float, float> pos);
            //void moveEntity(Game &game, std::string name, ::Network::MessageType type);
            void newMissile(Game &game, std::string name);
            void newEnemy(Game &game, std::string name);
    };
}

#endif /* GAME_NETWORK_HPP */
