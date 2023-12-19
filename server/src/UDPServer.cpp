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

    void UDPServer::newConnection(const std::string &name)
    {
        ecs::SceneManager &sceneManager = this->m_world.getSceneManager();
        ecs::Scene &scene = sceneManager.getCurrentScene();
        std::vector<ecs::Entity *> entities = sceneManager.view<ecs::Controllable, ecs::Health>(scene);

        if (entities.size() <= 4) {
            this->sendData(PacketType::CONNECTION_ACCEPTED, "Connection accepted, data will be sent...");
            std::vector<ecs::Entity *> entities = sceneManager.getEntities(scene);


            for (auto &entity : entities) {
                std::string entityData = "Entity:";
                entityData += std::to_string(entity->id);
                entityData += ";";
                for (auto &component : entity->components) {
                    if (component.first.find("Acceleration") != std::string::npos) {
                        ecs::Acceleration &acceleration = sceneManager.get<ecs::Acceleration>(*entity);
                        entityData += "Acceleration:";
                        entityData += std::to_string(acceleration.ddx);
                        entityData += ",";
                        entityData += std::to_string(acceleration.ddy);
                        entityData += ",";
                        entityData += std::to_string(acceleration.maxSpeed);
                        entityData += ";";
                    }
                    if (component.first.find("Animation") != std::string::npos) {
                        ecs::Animation &animation = sceneManager.get<ecs::Animation>(*entity);
                        entityData += "Animation:";
                        entityData += std::to_string(animation.currentFrame);
                        entityData += ",";
                        entityData += std::to_string(animation.frames);
                        entityData += ",";
                        entityData += std::to_string(animation.frameTime);
                        entityData += ",";
                        entityData += std::to_string(animation.offset.x);
                        entityData += ",";
                        entityData += std::to_string(animation.offset.y);
                        entityData += ",";
                        entityData += std::to_string(animation.offset.width);
                        entityData += ",";
                        entityData += std::to_string(animation.offset.height);
                        entityData += ";";
                    }
                    if (component.first.find("Collision") != std::string::npos) {
                        ecs::Collision &collision = sceneManager.get<ecs::Collision>(*entity);
                        entityData += "Collision:";
                        entityData += std::to_string(collision.isColliding);
                        for (auto &collidingEntity : collision.collidingWith) {
                            entityData += ",";
                            entityData += std::to_string(collidingEntity);
                        }
                        entityData += ";";
                    }
                    }
                this->sendData(PacketType::CREATE, entityData);
            }
            this->sendData(PacketType::END_OF_DATA, "End of data");
        } else {
            this->sendData(PacketType::CONNECTION_ACCEPTED, "Too many players");
        }
    }
}
