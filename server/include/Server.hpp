#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include "UDPServer.hpp"
#include "World.hpp"

namespace rtype {
    class Server {
        const unsigned short c_port;
        boost::asio::io_context m_io_context;
        ecs::World m_world;
        UDPServer m_udpServer;

        public:
            Server(const unsigned short port);
            ~Server();

            void run();
    };
}

#endif /* SERVER_HPP */
