#include "Network.hpp"
#include "Game.hpp"

namespace rtype {
    Network::Network() :
    m_socket(this->m_ioContext),
    m_running(true)
    {
    }

    Network::~Network()
    {
        this->m_ioContext.stop();
        for (auto& thread : this->m_threads) {
            thread.join();
        }
    }

    void Network::connect(std::string ip, int port, Game &game)
    {
        this->m_endpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(ip), port);
        this->m_socket.connect(this->m_endpoint);
        this->m_threads.emplace_back(std::thread(&Network::receive, this, std::ref(game)));

        this->send(::Network::MessageType::PlayerJoin, "Player1");
    }

    void Network::send(::Network::MessageType type, std::string message)
    {
        std::cout << "Sending message: " << message << std::endl;
        
        std::vector<char> sendBuffer(sizeof(::Network::MessageType) + message.size());

        *reinterpret_cast<::Network::MessageType*>(&sendBuffer[0]) = type;

        std::copy(message.begin(), message.end(), sendBuffer.begin() + sizeof(::Network::MessageType));

        this->m_socket.send_to(boost::asio::buffer(sendBuffer), this->m_endpoint);
    }

    void Network::receive(Game &game)
    {
        std::cout << "Receiving messages" << std::endl;

        while (this->m_running) {
            try {
                std::array<char, 1024> receiveBuffer;
                boost::asio::ip::udp::endpoint senderEndpoint;

                std::size_t bytes_transferred = this->m_socket.receive_from(boost::asio::buffer(receiveBuffer), senderEndpoint);

                if (bytes_transferred > 0) {
                    if(bytes_transferred >= sizeof(::Network::MessageType)) {
                        ::Network::MessageType messageType = *reinterpret_cast<::Network::MessageType*>(&receiveBuffer[0]);
                        std::string msg(receiveBuffer.data() + sizeof(::Network::MessageType), bytes_transferred - sizeof(::Network::MessageType));
                        if (messageType == ::Network::MessageType::PlayerJoin) {
                            this->newPlayerConnected(game, msg);
                        }
                    }
                }
            } catch (const std::exception &e) {
                std::cerr << "Error: " << e.what() << std::endl;
                exit(84);
            }
        }
        std::cout << "Stopped receiving messages" << std::endl;
    }

    void Network::newPlayerConnected(Game &game, std::string name)
    {
        std::cout << "New player connected: " << name << std::endl;
        auto &world = game.getWorld();
        float offset = game.getOffsetColorSpaceship();
        std::pair<float, float> pos = std::make_pair(static_cast<float>(rand() % 800), static_cast<float>(rand() % 450));

        ecs::Scene &inGame = world.getCurrentScene();
        ecs::Entity &player = world.createEntity(inGame);
        world.assign(player, ecs::Position{pos.first, pos.second});
        world.assign(player, ecs::Velocity{0, 0});
        world.assign(player, ecs::Sprite{"assets/characters.gif", ecs::Rectangle{0, offset, 32, 16}, ecs::Vector2{0, 0}});
        world.assign(player, ecs::Acceleration{0, 0, 4});
        world.assign(player, ecs::Scale{1, 1});
        world.assign(player, ecs::Rotation{0});
        world.assign(player, ecs::Name{name, ecs::Position{-20, -20}});

        Player newPlayer(player, name);

        game.addPlayer(newPlayer);
    }

    void Network::setRunning(bool running)
    {
        this->m_running = running;
    }
}
