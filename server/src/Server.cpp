#include "Server.hpp"

namespace server {
    Server::Server(short port)
    {
        setup(port);
        this->_world = ecs::World();

        ecs::Scene scene = this->_world.createScene();

        this->_world.registerSystems<
            ecs::MovementSystem,
            ecs::CollisionSystem,
            ecs::LifeSystem
        >(scene);

        ecs::Entity &ParallaxBack1 = this->_world.createEntity(scene);

        this->_world.assign(ParallaxBack1, ecs::Position{0, 0});
        this->_world.assign(ParallaxBack1, ecs::Velocity{-3, 0});
        this->_world.assign(ParallaxBack1, ecs::Sprite{"assets/space-back.png", ecs::Rectangle{0, 0, 7596, 1080}, ecs::Vector2{0, 0}});
        this->_world.assign(ParallaxBack1, ecs::Parallax{true});
        this->_world.assign(ParallaxBack1, ecs::Acceleration{0, 0, 3});
        this->_world.assign(ParallaxBack1, ecs::Scale{1, 1});
        this->_world.assign(ParallaxBack1, ecs::Rotation{0});

        ecs::Entity &ParallaxBack2 = this->_world.createEntity(scene);

        this->_world.assign(ParallaxBack2, ecs::Position{1920, 0});
        this->_world.assign(ParallaxBack2, ecs::Velocity{-1.5, 0});
        this->_world.assign(ParallaxBack2, ecs::Sprite{"assets/far-planets.png", ecs::Rectangle{0, 0, 272, 160}, ecs::Vector2{0, 0}});
        this->_world.assign(ParallaxBack2, ecs::Parallax{true});
        this->_world.assign(ParallaxBack2, ecs::Acceleration{0, 0, 2});
        this->_world.assign(ParallaxBack2, ecs::Scale{1920 / 272, 1080 / 160});
        this->_world.assign(ParallaxBack2, ecs::Rotation{0});
    }

    Server::~Server()
    {
    }

    void Server::setup(short port)
    {
        _endpoint = asio::ip::udp::endpoint(asio::ip::udp::v4(), asio::ip::port_type(port));
        _socket = std::make_shared<asio::ip::udp::socket>(_io_context, _endpoint);
    }

    void Server::run()
    {
        const frame tickDuration(1);

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

        std::chrono::time_point<std::chrono::steady_clock> fpsTimer = std::chrono::steady_clock::now();
        frame FPS{};

        while (true) {
            FPS = std::chrono::duration_cast<frame>(std::chrono::steady_clock::now() - fpsTimer);

            if (FPS >= tickDuration) {
                this->_world.update();
            }

            processMessages();

            if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - begin).count() > 2000 && _players.size() > 1) {
                std::cout << "Spawning enemy" << std::endl;

                begin = std::chrono::steady_clock::now();

                std::string tag = "enemy" + std::to_string(rand() % 1000);

                EntityTemplate entityTemplate = EntityTemplate();
                entityTemplate.enemy(this->_world, tag, 900, 100);

                for (auto &player : _players) {
                    ecs::Buffer buffer;
                    buffer.writeMessageType(ecs::MessageType::ENEMY_SPAWN);
                    std::string response = tag + ":900:100";
                    buffer.writeString(response);
                    send(buffer, player.getEndpoint());
                }
            }
        }
    }

    void Server::processMessages()
    {
        EntityTemplate entityTemplate = EntityTemplate();

        while (!this->bufferList.empty()) {
            this->mutex.lock();
            ecs::Buffer buffer = this->bufferList.front();
            this->bufferList.erase(this->bufferList.begin());
            this->mutex.unlock();

            ecs::MessageType messageType = buffer.readMessageType();
            std::string messageString = buffer.readString();

            std::cout << "Message received: " << messageString << std::endl;

            switch (messageType) {
                case ecs::MessageType::PLAYER_CONNECTED:
                {
                    Player newPlayer = Player(messageString, buffer.getEndpoint());

                    _players.push_back(newPlayer);

                    for (auto &player : _players) {
                        if (player.getEndpoint() != buffer.getEndpoint()) {
                            // Send to all other players that a new player has connected
                            ecs::Buffer newBuffer;
                            newBuffer.writeMessageType(ecs::MessageType::PLAYER_CONNECTED);
                            std::string response = messageString + ":" + "0" + ":100:100";
                            newBuffer.writeString(response);
                            send(newBuffer, player.getEndpoint());

                            // Send to the new player that all other players are connected
                            ecs::Buffer newBuffer2;
                            newBuffer2.writeMessageType(ecs::MessageType::PLAYER_CONNECTED);
                            std::string response2 = player.getName() + ":" + "0" + ":100:100";
                            newBuffer2.writeString(response2);
                            send(newBuffer2, buffer.getEndpoint());
                        }
                    }

                    ecs::Buffer localBuffer;
                    localBuffer.writeMessageType(ecs::MessageType::PLAYER_CONNECTED);
                    std::string response = messageString + ":" + "1" + ":100:100";
                    localBuffer.writeString(response);
                    send(localBuffer, buffer.getEndpoint());

                    entityTemplate.player(this->_world, messageString, 100, 100);
                    break;
                }
                case ecs::MessageType::PLAYER_MOVE:
                {
                    // Message format: "tag:direction"
                    std::string delimiter = ":";
                    std::string rawId = messageString.substr(0, messageString.find(delimiter));
                    messageString.erase(0, messageString.find(delimiter) + delimiter.length());
                    std::string direction = messageString.substr(0, messageString.find(delimiter));
                    std::size_t id = 0;

                    try {
                        id = std::stoi(rawId);
                    } catch (std::exception &e) {
                        std::cerr << "Exception in processMessages: " << e.what() << std::endl;
                        break;
                    }
                    ecs::Entity &e = this->_world.getEntityById(this->_world.getCurrentScene(), id);
                    auto &velocity = this->_world.get<ecs::Velocity>(e);

                    if (direction == "left") {
                        velocity.dx = -4;
                    } else if (direction == "right") {
                        velocity.dx = 4;
                    } else if (direction == "up") {
                        velocity.dy = -4;
                    } else if (direction == "down") {
                        velocity.dy = 4;
                    } else if (direction == "stopx") {
                        velocity.dx = 0;
                    } else if (direction == "stopy") {
                        velocity.dy = 0;
                    }

                    for (auto &player : _players) {
                        if (player.getEndpoint() != buffer.getEndpoint()) {
                            send(buffer, player.getEndpoint());
                        }
                    }
                    break;
                }
                case ecs::MessageType::PLAYER_SHOOT:
                {
                    std::size_t id = 0;

                    try {
                        id = std::stoi(messageString);
                    } catch (std::exception &e) {
                        std::cerr << "Exception in processMessages: " << e.what() << std::endl;
                        break;
                    }

                    ecs::Entity &e = this->_world.getEntityById(this->_world.getCurrentScene(), id);
                    auto &position = this->_world.get<ecs::Position>(e);
                    auto &sprite = this->_world.get<ecs::Sprite>(e);
                    auto &scale = this->_world.get<ecs::Scale>(e);

                    entityTemplate.playerBullet(this->_world, "", static_cast<int>(position.x + sprite.source.width * scale.x), static_cast<int>(position.y + (sprite.source.height * scale.y) / 2));

                    for (auto &player : _players) {
                        send(buffer, player.getEndpoint());
                    }
                    break;
                }
                case ecs::MessageType::PLAYER_DISCONNECTED:
                {
                    for (auto &player : _players) {
                        if (player.getEndpoint() != buffer.getEndpoint()) {
                            ecs::Buffer newBuffer;
                            newBuffer.writeMessageType(ecs::MessageType::PLAYER_DISCONNECTED);
                            newBuffer.writeString(messageString);
                            send(newBuffer, player.getEndpoint());
                        }
                    }

                    for (auto it = _players.begin(); it != _players.end(); ++it) {
                        if ((*it).getEndpoint() == buffer.getEndpoint()) {
                            _players.erase(it);
                            break;
                        }
                    }
                    break;
                }
                default:
                    break;
            }
        }
    }

    void Server::receive(ecs::Buffer &buffer)
    {
        try {
            asio::ip::udp::endpoint senderEndpoint;
            std::array<char, 1024> receiveBuffer;
            std::size_t bytes_transferred = this->_socket->receive_from(asio::buffer(receiveBuffer), senderEndpoint);

            if (bytes_transferred > 0) {
                buffer.setData(std::vector<char>(receiveBuffer.begin(), receiveBuffer.begin() + bytes_transferred));
                buffer.setEndpoint(senderEndpoint);
            }
        } catch (std::exception &e) {
            std::cerr << "Exception in receiveMessage: " << e.what() << std::endl;
        }
    }
