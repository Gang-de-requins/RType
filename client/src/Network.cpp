#include "Network.hpp"
#include "Game.hpp"
#include <exception>

namespace rtype {
    Network::Network() :
    m_socket(this->m_ioContext),
    m_running(true),
    m_connected(false)
    {
    }

    Network::~Network()
    {
        this->m_ioContext.stop();
        for (auto& thread : this->m_threads) {
            thread.join();
        }
    }

    void Network::connect(const std::string &ip, const unsigned short port, Game &game, const std::string &playerName)
    {
        this->m_endpoint = asio::ip::udp::endpoint(asio::ip::address::from_string(ip), port);
        this->m_socket.connect(this->m_endpoint);
        this->m_threads.emplace_back(std::thread(&Network::receive, this, std::ref(game)));

        std::cout << "Sending player name: " << playerName << std::endl;
        this->send(ecs::MessageType::PLAYER_CONNECTED, playerName);
        this->m_connected = true;
    }

    void Network::send(ecs::MessageType type, std::string message)
    {
        ecs::Buffer buffer;

        buffer.writeMessageType(type);
        buffer.writeString(message);
        // std::cout << "Received MessageType: " << static_cast<int>(buffer.readMessageType()) << std::endl;
        this->m_socket.send_to(asio::buffer(buffer.getData()), this->m_endpoint);
    }

    void Network::receive(Game &game)
    {
        std::vector<ecs::MessageType> commands = {
            ecs::MessageType::PLAYER_CONNECTED,
            ecs::MessageType::PLAYER_DISCONNECTED,
            ecs::MessageType::PLAYER_MOVE,
            ecs::MessageType::PLAYER_SHOOT,
            ecs::MessageType::ENEMY_SPAWN,
            ecs::MessageType::ENEMY_SHOOT,
            ecs::MessageType::ENTITY_DESTROYED
        };

        while (this->m_running) {
            try {
                std::array<char, 1024> receiveBuffer;
                asio::ip::udp::endpoint senderEndpoint;

                std::size_t bytes_transferred = this->m_socket.receive_from(asio::buffer(receiveBuffer), senderEndpoint);

                if (bytes_transferred > 0) {
                    if(bytes_transferred >= sizeof(::Network::MessageType)) {
                        ecs::Buffer buffer;
                        buffer.getData() = std::vector<char>(receiveBuffer.begin(), receiveBuffer.begin() + bytes_transferred);

                        ecs::MessageType messageType = buffer.readMessageType();
                        std::string msg = buffer.readString();

                        // std::cout << msg << std::endl;

                        // if (messageType == ecs::MessageType::PLAYER_CONNECTED) {
                        //     this->newPlayerConnected(game, msg);
                        // }

                        switch (messageType) {
                            case ecs::MessageType::PLAYER_CONNECTED:
                                std::cout << "New player connected: " << msg << std::endl;
                                this->newPlayerConnected(game, msg);
                                break;
                            case ecs::MessageType::PLAYER_DISCONNECTED:
                                std::cout << "Player disconnected: " << msg << std::endl;
                                this->playerDisconnected(game, msg);
                                break;
                            case ecs::MessageType::PLAYER_MOVE:
                                std::cout << "Player move: " << msg << std::endl;
                                this->moveEntity(game, msg);
                                break;
                            case ecs::MessageType::PLAYER_SHOOT:
                                std::cout << "Player shoot: " << msg << std::endl;
                                this->newMissile(game, msg);
                                break;
                            case ecs::MessageType::ENEMY_SPAWN:
                                std::cout << "Enemy spawn: " << msg << std::endl;
                                this->newEnemy(game, msg);
                                break;
                            case ecs::MessageType::ENEMY_SHOOT:
                                break;
                            case ecs::MessageType::ENTITY_DESTROYED:
                                this->playerDisconnected(game, msg);
                                break;
                            default:
                                break;
                        }
                    }
                }
            } catch (const std::exception &e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
        std::cout << "Stopped receiving messages" << std::endl;
    }

    void Network::setRunning(bool running)
    {
        this->m_running = running;
    }

    bool Network::isConnected() const
    {
        return this->m_connected;
    }

    /* ---------------------------- PRIVATE FUNCTIONS --------------------------- */

    void Network::newPlayerConnected(Game &game, std::string name)
    {
        std::cout << "New player connected: " << name << std::endl;
        auto &world = game.getWorld();

        std::string playerName = name.substr(0, name.find(":"));
        bool isMe = name.substr(name.find(":") + 1, name.substr(name.find(":") + 1).find(":")) == "1";
        std::string rawPos = name.substr(name.find(":") + 1);
        rawPos = rawPos.substr(rawPos.find(":") + 1);
        std::pair<float, float> pos = std::make_pair(std::stof(rawPos.substr(0, rawPos.find(":"))), std::stof(rawPos.substr(rawPos.find(":") + 1)));

        ecs::Scene &inGame = game.getWorld().getCurrentScene();
        ecs::Entity &player = game.getWorld().createEntity(inGame);

        world.assign(player, ecs::Position{pos.first, pos.second});
        world.assign(player, ecs::Velocity{0, 0});
        world.assign(player, ecs::Sprite{"assets/characters2.gif", ecs::Rectangle{0, 0, 32, 32}, ecs::Vector2{0, 0}});
        world.assign(player, ecs::Acceleration{0, 0, 4});
        world.assign(player, ecs::Scale{1, 1});
        world.assign(player, ecs::Rotation{0});
        world.assign(player, ecs::Name{playerName, ecs::Position{-20, -20}});
        world.assign(player, ecs::Collision{false, {}, true});
        world.assign(player, ecs::Animation{ecs::Rectangle{0, 0, 32, 0}, 8, 0, 150, std::chrono::steady_clock::now()});

        if (isMe) {
            world.assign(player, ecs::Controllable{
                std::unordered_map<int, std::tuple<ecs::ActionTrigger, std::function<void(ecs::SceneManager & sceneManager, ecs::Scene & scene, ecs::Entity * entity)>>> {
                    {KEY_UP, std::make_tuple<ecs::ActionTrigger, std::function<void(ecs::SceneManager&, ecs::Scene&, ecs::Entity*)>>(
                        ecs::ActionTrigger::Hold, [](ecs::SceneManager& sceneManager, ecs::Scene& scene, ecs::Entity* entity) {
                            static_cast<void>(sceneManager);

                            scene.events[ecs::EventType::Input].push_back({
                                ecs::GameEvent::MoveUp,
                                {entity}
                            });
                        }
                    )},
                    {KEY_DOWN, std::make_tuple<ecs::ActionTrigger, std::function<void(ecs::SceneManager&, ecs::Scene&, ecs::Entity*)>>(
                        ecs::ActionTrigger::Hold, [](ecs::SceneManager& sceneManager, ecs::Scene& scene, ecs::Entity* entity) {
                            static_cast<void>(sceneManager);

                            scene.events[ecs::EventType::Input].push_back({
                                ecs::GameEvent::MoveDown,
                                {entity}
                            });
                        }
                    )},
                    {KEY_LEFT, std::make_tuple<ecs::ActionTrigger, std::function<void(ecs::SceneManager&, ecs::Scene&, ecs::Entity*)>>(
                        ecs::ActionTrigger::Hold, [](ecs::SceneManager& sceneManager, ecs::Scene& scene, ecs::Entity* entity) {
                            static_cast<void>(sceneManager);

                            scene.events[ecs::EventType::Input].push_back({
                                ecs::GameEvent::MoveLeft,
                                {entity}
                            });
                        }
                    )},
                    {KEY_RIGHT, std::make_tuple<ecs::ActionTrigger, std::function<void(ecs::SceneManager&, ecs::Scene&, ecs::Entity*)>>(
                        ecs::ActionTrigger::Hold, [](ecs::SceneManager& sceneManager, ecs::Scene& scene, ecs::Entity* entity) {
                            static_cast<void>(sceneManager);

                            scene.events[ecs::EventType::Input].push_back({
                                ecs::GameEvent::MoveRight,
                                {entity}
                            });
                        }
                    )},
                    {KEY_SPACE, std::make_tuple<ecs::ActionTrigger, std::function<void(ecs::SceneManager&, ecs::Scene&, ecs::Entity*)>>(
                        ecs::ActionTrigger::Press, [](ecs::SceneManager& sceneManager, ecs::Scene& scene, ecs::Entity* entity) {
                            if (sceneManager.has<ecs::Shooter>(*entity)) {
                                ecs::Shooter& shooter = sceneManager.get<ecs::Shooter>(*entity);

                                if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - shooter.lastShotTime) >= shooter.cooldown) {
                                    shooter.lastShotTime = std::chrono::steady_clock::now();
                                    scene.events[ecs::EventType::Spawn].push_back({
                                        ecs::GameEvent::SpawnPlayerBullet,
                                        {entity}
                                    });
                                }
                            }
                        }
                    )},
                }
            });
            game.setId(player.id);
        }

        Player newPlayer(player, playerName);

        game.addPlayer(newPlayer);
    }

    void Network::playerDisconnected(Game &game, std::string msg)
    {
        std::size_t id = 0;
        
        try {
            id = std::stoi(msg);
        } catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return;
        }

        ecs::World &world = game.getWorld();

        for (auto &player : game.getPlayers()) {
            if (player.getId() == id) {
                ecs::Entity &e = world.getEntityById(world.getCurrentScene(), id);
                world.destroyEntity(world.getCurrentScene(), e);
                player.setAlive(false);
                break;
            }
        }
    }

    void Network::moveEntity(Game &game, std::string msg)
    {
        std::size_t id = 0;
        std::string rawId = msg.substr(0, msg.find(":"));

        try {
            id = std::stoi(rawId);
        } catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return;
        }

        for (auto &player : game.getPlayers()) {
            if (player.getId() == id) {
                player.move(game, msg);
            }
        }
    }

    void Network::newMissile(Game &game, std::string name)
    {
        std::size_t id = 0;

        try {
            id = std::stoi(name);
        } catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return;
        }

        for (auto &player : game.getPlayers()) {
            if (player.getId() == id) {
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
