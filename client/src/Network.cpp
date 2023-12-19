#include "Network.hpp"

namespace rtype_client {
    Network::Network(const std::string &host, const unsigned short portUDP, const std::string &name) :
    m_udpClient(this->m_io_context, host, portUDP, name)
    {
    }

    Network::~Network()
    {
    }

    void Network::run()
    {
        this->m_udpClient.start();
    }
}
