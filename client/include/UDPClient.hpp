#ifndef UDP_CLIENT_HPP
#define UDP_CLIENT_HPP

#include <iostream>
#include <boost/asio.hpp>
#include "Protocol.hpp"

namespace rtype_client {
    class UDPClient {
        boost::asio::ip::udp::socket m_socket;
        boost::asio::ip::udp::endpoint m_serverEndpoint;
        const std::string m_name;

        public:
            UDPClient(boost::asio::io_context &io_context, const std::string &serverAddress, unsigned short serverPort, const std::string &name);

            void start();

        private:
            void sendConnectionMessage(const std::string& name);
    };
}

#endif /* UDP_CLIENT_HPP */
