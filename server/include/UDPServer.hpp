#ifndef UDP_SERVER_HPP
#define UDP_SERVER_HPP

#include <iostream>
#include <boost/asio.hpp>
#include "Protocol.hpp"

namespace rtype {
    class UDPServer {
        const unsigned short c_port;
        boost::asio::ip::udp::socket m_socket;
        boost::asio::ip::udp::endpoint m_serverEndpoint;
        boost::asio::ip::udp::endpoint m_remoteEndpoint;
        std::array<char, 1024> m_recvBuffer;

        public:
            UDPServer(boost::asio::io_context &io_context, const unsigned short port);
            ~UDPServer();

        private:
            void startReceive();
            void handleReceive(const boost::system::error_code &error, std::size_t bytes_transferred);
            void handlePacket(const Packet &packet);
    };
}

#endif /* UDP_SERVER_HPP */
