#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <deque>
#include <memory>
#include <vector>
#include "Room.hpp"

namespace rtype {
    class Server {
        const unsigned short c_port;
        std::vector<std::unique_ptr<Room>> m_rooms;
        asio::io_service m_ioService;
        asio::ip::tcp::acceptor m_acceptor;
        asio::ip::tcp::socket m_socket;

        public:
            Server(const unsigned short port);

            void startAccept();
            void handleClients();
    };
}

#endif /* SERVER_HPP */
