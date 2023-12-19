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
                    if (component.first.find("Color") != std::string::npos) {
                        ecs::Color &color = sceneManager.get<ecs::Color>(*entity);
                        entityData += "Color:";
                        entityData += std::to_string(color.r);
                        entityData += ",";
                        entityData += std::to_string(color.g);
                        entityData += ",";
                        entityData += std::to_string(color.b);
                        entityData += ",";
                        entityData += std::to_string(color.a);
                        entityData += ";";
                    }
                    if (component.first.find("Controllable") != std::string::npos) {
                        ecs::Controllable &controllable = sceneManager.get<ecs::Controllable>(*entity);
                        entityData += "Controllable:";
                        entityData += std::to_string(controllable.keyUp);
                        entityData += ",";
                        entityData += std::to_string(controllable.keyDown);
                        entityData += ",";
                        entityData += std::to_string(controllable.keyLeft);
                        entityData += ",";
                        entityData += std::to_string(controllable.keyRight);
                        entityData += ",";
                        entityData += std::to_string(controllable.keySpace);
                        entityData += ";";
                    }
                    if (component.first.find("Damage") != std::string::npos) {
                        ecs::Damage &damage = sceneManager.get<ecs::Damage>(*entity);
                        entityData += "Damage:";
                        entityData += std::to_string(damage.damage);
                        entityData += ";";
                    }
                    if (component.first.find("FontSize") != std::string::npos) {
                        ecs::FontSize &fontSize = sceneManager.get<ecs::FontSize>(*entity);
                        entityData += "FontSize:";
                        entityData += std::to_string(fontSize.size);
                        entityData += ";";
                    }
                    if (component.first.find("Health") != std::string::npos) {
                        ecs::Health &health = sceneManager.get<ecs::Health>(*entity);
                        entityData += "Health:";
                        entityData += std::to_string(health.health);
                        entityData += ";";
                    }
                    if (component.first.find("Music") != std::string::npos) {
                        ecs::Music &music = sceneManager.get<ecs::Music>(*entity);
                        entityData += "Music:";
                        entityData += music.path;
                        entityData += ";";
                    }
                    if (component.first.find("Name") != std::string::npos) {
                        ecs::Name &name = sceneManager.get<ecs::Name>(*entity);
                        entityData += "Name:";
                        entityData += name.name;
                        entityData += ",";
                        entityData += std::to_string(name.position.x);
                        entityData += ",";
                        entityData += std::to_string(name.position.y);
                        entityData += ";";
                    }
                    if (component.first.find("Position") != std::string::npos) {
                        ecs::Position &position = sceneManager.get<ecs::Position>(*entity);
                        entityData += "Position:";
                        entityData += std::to_string(position.x);
                        entityData += ",";
                        entityData += std::to_string(position.y);
                        entityData += ";";
                    }
                    if (component.first.find("Rectangle") != std::string::npos) {
                        ecs::Rectangle &rectangle = sceneManager.get<ecs::Rectangle>(*entity);
                        entityData += "Rectangle:";
                        entityData += std::to_string(rectangle.x);
                        entityData += ",";
                        entityData += std::to_string(rectangle.y);
                        entityData += ",";
                        entityData += std::to_string(rectangle.width);
                        entityData += ",";
                        entityData += std::to_string(rectangle.height);
                        entityData += ";";
                    }
                    if (component.first.find("Rotation") != std::string::npos) {
                        ecs::Rotation &rotation = sceneManager.get<ecs::Rotation>(*entity);
                        entityData += "Rotation:";
                        entityData += std::to_string(rotation.angle);
                        entityData += ";";
                    }
                    if (component.first.find("Scale") != std::string::npos) {
                        ecs::Scale &scale = sceneManager.get<ecs::Scale>(*entity);
                        entityData += "Scale:";
                        entityData += std::to_string(scale.x);
                        entityData += ",";
                        entityData += std::to_string(scale.y);
                        entityData += ";";
                    }
                    if (component.first.find("Sound") != std::string::npos) {
                        ecs::Sound &sound = sceneManager.get<ecs::Sound>(*entity);
                        entityData += "Sound:";
                        entityData += sound.path;
                        entityData += ";";
                    }
                    if (component.first.find("Sprite") != std::string::npos) {
                        ecs::Sprite &sprite = sceneManager.get<ecs::Sprite>(*entity);
                        entityData += "Sprite:";
                        entityData += sprite.path;
                        entityData += ";";
                    }
                    if (component.first.find("Text") != std::string::npos) {
                        ecs::Text &text = sceneManager.get<ecs::Text>(*entity);
                        entityData += "Text:";
                        entityData += text.content;
                        entityData += ";";
                    }
                    if (component.first.find("Velocity") != std::string::npos) {
                        ecs::Velocity &velocity = sceneManager.get<ecs::Velocity>(*entity);
                        entityData += "Velocity:";
                        entityData += std::to_string(velocity.dx);
                        entityData += ",";
                        entityData += std::to_string(velocity.dy);
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
