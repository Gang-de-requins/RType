#include "UDPClient.hpp"

namespace rtype_client {
    UDPClient::UDPClient(boost::asio::io_context &io_context, const std::string &host, const unsigned short port, const std::string &name) :
    m_socket(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0)),
    m_serverEndpoint(boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(host), port)),
    m_name(name)
    {
    }

    void UDPClient::start()
    {
        this->sendConnectionMessage(this->m_name);
    }

    /* --------------------------- PRIVATE METHODS --------------------------- */

    void UDPClient::sendConnectionMessage(const std::string &name)
    {
        Packet connectionMessage;
        connectionMessage.type = PacketType::CONNECT;
        connectionMessage.data = name;

        std::ostringstream archiveStream;
        boost::archive::binary_oarchive archive(archiveStream);
        archive << connectionMessage;

        std::string serializedMessage = archiveStream.str();

        std::cout << "Sending connection message: " << serializedMessage << std::endl;
        this->m_socket.async_send_to(
            boost::asio::buffer(serializedMessage),
            this->m_serverEndpoint,
            [this](const boost::system::error_code &error, std::size_t /* bytesSent */) {
                if (error) {
                    std::cerr << "Error sending data: " << error.message() << std::endl;
                }
            }
        );
    }
}
