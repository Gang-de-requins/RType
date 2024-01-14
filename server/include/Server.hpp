#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <memory>
#include <chrono>
#include <utility>
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
#include "WaveManager.hpp"

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
            void receive(ecs::Message &message);
            void sendGameState();

            template <typename T>
            void send(T &data, ecs::MessageType messageType, const asio::ip::udp::endpoint& recipientEndpoint) {
                std::vector<char> serializedData = data.serialize();
                std::size_t dataSize = serializedData.size();
                std::vector<char> packet(sizeof(std::size_t) + sizeof(ecs::MessageType) + dataSize);
                std::memcpy(packet.data(), &dataSize, sizeof(dataSize));
                std::memcpy(packet.data() + sizeof(dataSize), &messageType, sizeof(messageType));
                std::memcpy(packet.data() + sizeof(dataSize) + sizeof(ecs::MessageType), serializedData.data(), dataSize);
                this->_socket->send_to(asio::buffer(packet), recipientEndpoint);
            }

            std::vector<ecs::Message> messageList;
            std::mutex mutex;

            std::vector<Player> getPlayers() const { return _players; }

        private:
            std::shared_ptr<asio::ip::udp::socket> _socket;
            asio::ip::udp::endpoint _endpoint;
            asio::io_context _io_context;

            WaveManager waveManger;
            std::vector<Player> _players;
            ecs::World _world;
            int _maxEnemies = 45;
            int _nbEnemiesSpawned = 0;
    };
}

#endif /* SERVER_HPP */
