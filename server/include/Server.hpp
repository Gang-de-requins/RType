#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <memory>
#include <chrono>
#include <vector>
#include <mutex>
#if defined(_WIN32)
    #define NOGDI
    #define NOUSER
#endif

#include <asio.hpp>

#if defined(_WIN32)
    #undef near
    #undef far
#endif
#include "MessageType.hpp"
#include "Player.hpp"
#include "EntityTemplate.hpp"
#include "GameEngine.hpp"
#include "systems/Movement.hpp"

using frame = std::chrono::duration<int32_t, std::ratio<1, 60>>;
using ms = std::chrono::duration<int32_t, std::milli>;

namespace server {
    class Server {
        public:
            Server(short port);
            ~Server();

            void setup(short port);
            void run();
            void processMessages();
            void receive(ecs::Buffer &buffer);
            void send(ecs::Buffer &buffer, const asio::ip::udp::endpoint &endpoint);

            std::vector<ecs::Buffer> bufferList;
            std::mutex mutex;

            std::vector<Player> getPlayers() const { return _players; }


        private:
            std::shared_ptr<asio::ip::udp::socket> _socket;
            asio::ip::udp::endpoint _endpoint;
            asio::io_context _io_context;

            std::vector<Player> _players;
            ecs::World _world;
    };
}

#endif /* SERVER_HPP */
