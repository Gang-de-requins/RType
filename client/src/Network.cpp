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

    void Network::connect(const std::string &ip, const unsigned short port, Game &game)
    {
        this->m_endpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(ip), port);
        this->m_socket.connect(this->m_endpoint);
        this->m_threads.emplace_back(std::thread(&Network::receive, this, std::ref(game)));

        this->send(ecs::MessageType::PlayerJoin, playerName);
    }

    void Network::send(ecs::MessageType type, std::string message)
    {
        ecs::Buffer buffer;

        buffer.writeMessageType(type);
        buffer.writeString(message);
        std::cout << "Received MessageType: " << static_cast<int>(buffer.readMessageType()) << std::endl;
        this->m_socket.send_to(boost::asio::buffer(buffer.getData()), this->m_endpoint);
    }

    void Network::receive(Game &game)
    {
        std::vector<ecs::MessageType> directions = {
        ecs::MessageType::GoRight,
        ecs::MessageType::GoLeft,
        ecs::MessageType::GoTop,
        ecs::MessageType::GoBottom,
        ecs::MessageType::StopRight,
        ecs::MessageType::StopLeft,
        ecs::MessageType::StopTop,
        ecs::MessageType::StopBottom,
        };

        while (this->m_running) {
            try {
                std::array<char, 1024> receiveBuffer;
                boost::asio::ip::udp::endpoint senderEndpoint;

                std::size_t bytes_transferred = this->m_socket.receive_from(boost::asio::buffer(receiveBuffer), senderEndpoint);

                if (bytes_transferred > 0) {
                    if(bytes_transferred >= sizeof(::Network::MessageType)) {
                        //::Network::MessageType messageType = *reinterpret_cast<::Network::MessageType*>(&receiveBuffer[0]);
                        //std::string msg(receiveBuffer.data() + sizeof(::Network::MessageType), bytes_transferred - sizeof(::Network::MessageType));
                        // if (messageType == ::Network::MessageType::PlayerJoin) {
                        //     this->newPlayerConnected(game, msg);
                        // } else if (std::find(directions.begin(), directions.end(), messageType) != directions.end()) {
                        //     this->moveEntity(game, msg, messageType);
                        // }
                        // } else if (messageType == ::Network::MessageType::NewMissile) {
                        //     this->newMissile(game, msg);
                        // } else if (messageType == ::Network::MessageType::NewEnemy) {
                        //     this->newEnemy(game, msg);
                        // }
                    ecs::Buffer buffer;
                    buffer.getData() = std::vector<char>(receiveBuffer.begin(), receiveBuffer.begin() + bytes_transferred);

                    ecs::MessageType messageType = buffer.readMessageType();
                    std::string msg = buffer.readString();

                    std::cout << msg << std::endl;

                    if (messageType == ecs::MessageType::PlayerJoin) {
                        this->newPlayerConnected(game, msg);
                    } else if (std::find(directions.begin(), directions.end(), messageType) != directions.end()) {
                        this->moveEntity(game, msg, messageType);
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

    void Network::setRunning(bool running)
    {
        this->m_running = running;
    }

    /* ---------------------------- PRIVATE FUNCTIONS --------------------------- */

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
        world.assign(player, ecs::Sprite{"assets/characters2.gif", ecs::Rectangle{0, offset, 32, 16}, ecs::Vector2{0, 0}});
        world.assign(player, ecs::Acceleration{0, 0, 4});
        world.assign(player, ecs::Scale{1, 1});
        world.assign(player, ecs::Rotation{0});
        world.assign(player, ecs::Name{name, ecs::Position{-20, -20}});

        Player newPlayer(player, name);

        game.addPlayer(newPlayer);
    }

    void Network::moveEntity(Game &game, std::string name, ecs::MessageType direction)
    {
        for (auto &player : game.getPlayers()) {
            if (player.getName() == name) {
                player.move(game, direction);
            }
        }
    }

    void Network::newMissile(Game &game, std::string name)
    {
        for (auto &player : game.getPlayers()) {
            if (player.getName() == name) {
                player.shoot(game);
            }
        }
    }

    void Network::newEnemy(Game &game, std::string name)
    {
        auto &world = game.getWorld();
        ecs::Scene &inGame = world.getCurrentScene();
        std::string rawPos = name.substr(name.find(":") + 1);
        std::pair<float, float> pos = std::make_pair(std::stof(rawPos.substr(0, rawPos.find(":"))), std::stof(rawPos.substr(rawPos.find(":") + 1)));

        ecs::Entity &enemy = world.createEntity(inGame);
        world.assign(enemy, ecs::Position{pos.first, pos.second});
        world.assign(enemy, ecs::Velocity{-3, 0});
        world.assign(enemy, ecs::Sprite{"assets/characters.gif", ecs::Rectangle{0, 0, 32, 16}, ecs::Vector2{0, 0}});
        world.assign(enemy, ecs::Acceleration{0, 0, 4});
        world.assign(enemy, ecs::Scale{1, 1});
        world.assign(enemy, ecs::Rotation{0});
        world.assign(enemy, ecs::Name{"enemy", ecs::Position{-20, -20}});
        world.assign(enemy, ecs::Health{50});
        world.assign(enemy, ecs::Collision{false, {}, true});
        world.assign(enemy, ecs::Damage{30});
    }
}
