#ifndef GAME_NETWORK_HPP
#define GAME_NETWORK_HPP

#include <thread>
#include "UDPClient.hpp"

namespace rtype_client {
    class Network {
        boost::asio::io_context m_io_context;
        std::thread m_thread;
        UDPClient m_udpClient;

        public:
            Network(const std::string &host, const unsigned short portUDP, const std::string &name);
            ~Network();

            void run();
    };
}

#endif /* GAME_NETWORK_HPP */
