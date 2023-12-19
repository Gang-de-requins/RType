#include "UDPServer.hpp"

namespace rtype {
    UDPServer::UDPServer(boost::asio::io_context &io_context, const unsigned short port) :
    c_port(port),
    m_socket(io_context,boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)),
    m_serverEndpoint(boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port))
    {
        this->startReceive();
    }

    UDPServer::~UDPServer()
    {
    }

    void UDPServer::startReceive()
    {
        m_socket.async_receive_from(
            boost::asio::buffer(this->m_recvBuffer),
            this->m_remoteEndpoint,
            [this](const boost::system::error_code &error, std::size_t bytes_transferred) {
                this->handleReceive(error, bytes_transferred);
            }
        );
    }

    void UDPServer::handleReceive(const boost::system::error_code &error, std::size_t bytes_transferred)
    {
        if (!error || error == boost::asio::error::message_size) {
            std::cout << "Nb bytes received: " << bytes_transferred << " from " << this->m_remoteEndpoint.address() << ":" << this->m_remoteEndpoint.port() << " with content: " << this->m_recvBuffer.data() << std::endl;
            Packet packet;
            try {
                std::string str(this->m_recvBuffer.data(), bytes_transferred);
                std::cout << "str: " << str << std::endl;
                std::istringstream archiveStream(std::string(this->m_recvBuffer.data(), bytes_transferred));
                boost::archive::binary_iarchive archive(archiveStream);
                archive >> packet;
            } catch (const boost::archive::archive_exception &e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }

            this->handlePacket(packet);
            this->startReceive();
        } else {
            std::cerr << "Error: " << error.message() << std::endl;
        }
    }

    void UDPServer::handlePacket(const Packet &packet)
    {
        switch (packet.type) {
            case PacketType::CONNECT:
                std::cout << "New connection from " << this->m_remoteEndpoint.address() << ":" << this->m_remoteEndpoint.port() << " with name: " << packet.data << std::endl;
                break;
            case PacketType::DISCONNECT:
                break;
            default:
                std::cerr << "Unknown packet type" << std::endl;
                break;
        }
    }

    void UDPServer::sendData(PacketType type, const std::string &data)
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
            this->m_remoteEndpoint,
            [this](const boost::system::error_code &error, std::size_t /* bytesSent */) {
                if (error) {
                    std::cerr << "Error sending data: " << error.message() << std::endl;
                }
            }
        );
    }
}
