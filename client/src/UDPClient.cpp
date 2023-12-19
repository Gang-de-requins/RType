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
        this->sendData(PacketType::CONNECT, this->m_name);
    }

    /* --------------------------- PRIVATE METHODS --------------------------- */

    void UDPClient::sendData(PacketType type, const std::string &data)
    {
        Packet packet;
        packet.type = type;
        packet.data = data;

        std::ostringstream archiveStream;
        boost::archive::binary_oarchive archive(archiveStream);
        archive << packet;

        std::string serializedMessage = archiveStream.str();

        std::cout << "Sending data: " << serializedMessage << std::endl;
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
