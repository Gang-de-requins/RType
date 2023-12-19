#include "Server.hpp"

namespace rtype {
    Server::Server(const unsigned short port) :
    c_port(port),
    m_udpServer(this->m_io_context, port)
    {
    }

    Server::~Server()
    {
    }

    void Server::run()
    {
        this->m_io_context.run();
    }
}
