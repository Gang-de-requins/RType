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

        // ecs::Entity &ParallaxBack1 = this->_world.createEntity(scene);

        // this->_world.assign(ParallaxBack1, ecs::Position{0, 0});
        // this->_world.assign(ParallaxBack1, ecs::Velocity{-3, 0});
        // this->_world.assign(ParallaxBack1, ecs::Sprite{"assets/space-back.png", ecs::Rectangle{0, 0, 7596, 1080}, ecs::Vector2{0, 0}});
        // this->_world.assign(ParallaxBack1, ecs::Parallax{true});
        // this->_world.assign(ParallaxBack1, ecs::Acceleration{0, 0, 3});
        // this->_world.assign(ParallaxBack1, ecs::Scale{1, 1});
        // this->_world.assign(ParallaxBack1, ecs::Rotation{0});

        // ecs::Entity &ParallaxBack2 = this->_world.createEntity(scene);

        // this->_world.assign(ParallaxBack2, ecs::Position{1920, 0});
        // this->_world.assign(ParallaxBack2, ecs::Velocity{-1.5, 0});
        // this->_world.assign(ParallaxBack2, ecs::Sprite{"assets/far-planets.png", ecs::Rectangle{0, 0, 272, 160}, ecs::Vector2{0, 0}});
        // this->_world.assign(ParallaxBack2, ecs::Parallax{true});
        // this->_world.assign(ParallaxBack2, ecs::Acceleration{0, 0, 2});
        // this->_world.assign(ParallaxBack2, ecs::Scale{1920 / 272, 1080 / 160});
        // this->_world.assign(ParallaxBack2, ecs::Rotation{0});
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

        // std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

        std::chrono::time_point<std::chrono::steady_clock> fpsTimer = std::chrono::steady_clock::now();
        frame FPS{};

        while (true) {
            FPS = std::chrono::duration_cast<frame>(std::chrono::steady_clock::now() - fpsTimer);

            if (FPS >= tickDuration) {
                this->_world.update();
            }

            processMessages();

            // if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - begin).count() > 2000 && _players.size() > 1) {
            //     std::cout << "Spawning enemy" << std::endl;

            //     begin = std::chrono::steady_clock::now();

            //     std::string tag = "enemy" + std::to_string(rand() % 1000);

            //     EntityTemplate entityTemplate = EntityTemplate();
            //     entityTemplate.enemy(this->_world, tag, 900, 100);

            //     for (auto &player : _players) {
            //         ecs::Buffer buffer;
            //         buffer.writeMessageType(ecs::MessageType::ENEMY_SPAWN);
            //         std::string response = tag + ":900:100";
            //         buffer.writeString(response);
            //         send(buffer, player.getEndpoint());
            //     }
            // }
        }
    }

    void Server::processMessages()
    {
        EntityTemplate entityTemplate = EntityTemplate();

        while (!this->messageList.empty()) {
            this->mutex.lock();
            ecs::Message message = this->messageList.front();
            this->messageList.erase(this->messageList.begin());
            this->mutex.unlock();

            ecs::MessageType messageType = message.getMessageType();

            switch (messageType) {
            case ecs::MessageType::PlayerJoined: {
                ecs::PlayerJoined receivedStruct;
                receivedStruct.deserialize(message.getMessageData());
                std::cout << "Received PlayerJoinRequest: playername = " << receivedStruct.playername << std::endl;
                Player newPlayer = Player(receivedStruct.playername, message.getEndpoint());
                entityTemplate.player(this->_world, receivedStruct.playername, 100, 20);
                auto &scene = this->_world.getCurrentScene();
                newPlayer.setId(this->_world.getEntityById(scene, scene.entities.size() - 1).id);
                _players.push_back(newPlayer);

                ecs::NewPlayer newPlayerstr = {newPlayer.getName(), 0, {0, 0}, 100};
                send(newPlayerstr, ecs::MessageType::PlayerJoinedAccept, message.getEndpoint());

                for (auto& entity : _players) {
                        if (entity.getName() != newPlayer.getName()) {
                            ecs::NewPlayer existingPlayer = {entity.getName(), 0, {0, 0}, 100};
                            send(existingPlayer, ecs::MessageType::NewPlayer, message.getEndpoint());
                            send(newPlayerstr, ecs::MessageType::NewPlayer, entity.getEndpoint());
                        }
                    }
                }
                break;
            case ecs::MessageType::NewMissile: {
                for (auto &player : _players) {
                    if (player.getEndpoint() == message.getEndpoint()) {
                        ecs::Entity &e = this->_world.getEntityById(this->_world.getCurrentScene(), player.getId());
                        auto &position = this->_world.get<ecs::Position>(e);
                        auto &sprite = this->_world.get<ecs::Sprite>(e);
                        auto &scale = this->_world.get<ecs::Scale>(e);
                        std::cout << "New missile predator" << std::endl;
                        entityTemplate.playerBullet(this->_world, "", static_cast<int>(position.x + sprite.source.width * scale.x), static_cast<int>(position.y + (sprite.source.height * scale.y) / 2));
                    }
                }
                break;
            }
            case ecs::MessageType::Move: {
                ecs::Move receivedStruct;
                receivedStruct.deserialize(message.getMessageData());
                for (auto &player : _players) {
                    if (player.getEndpoint() == message.getEndpoint()) {
                        std::cout << player.getId() << std::endl;
                        ecs::Entity &e = this->_world.getEntityById(this->_world.getCurrentScene(), player.getId());
                        auto &pos = this->_world.get<ecs::Position>(e);

                        if (receivedStruct.direction == ecs::MessageType::GoLeft)
                            pos.x -= 4;
                        if (receivedStruct.direction == ecs::MessageType::GoRight)
                            pos.x += 4;
                        if (receivedStruct.direction == ecs::MessageType::GoTop)
                            pos.y -= 4;
                        if (receivedStruct.direction == ecs::MessageType::GoBottom)
                            pos.y += 4;
                    }
                }
                break;
            }
            default:
                std::cout << "Unknown message type received: " << static_cast<int>(message.getMessageType()) << std::endl;
                break;
        }
    }
    }
            // switch (messageType) {
            //     case ecs::MessageType::PLAYER_CONNECTED:
            //     {
            //         Player newPlayer = Player(messageString, buffer.getEndpoint());

            //         _players.push_back(newPlayer);

            //         entityTemplate.player(this->_world, messageString, 100, y);

            //         break;
            //     }
            //     case ecs::MessageType::PLAYER_MOVE:
            //     {
            //         // Message format: "tag:direction"
            //         std::string delimiter = ":";
            //         std::string rawId = messageString.substr(0, messageString.find(delimiter));
            //         messageString.erase(0, messageString.find(delimiter) + delimiter.length());
            //         std::string direction = messageString.substr(0, messageString.find(delimiter));
            //         std::size_t id = 0;

            //         try {
            //             id = std::stoi(rawId);
            //         } catch (std::exception &e) {
            //             std::cerr << "Exception in processMessages: " << e.what() << std::endl;
            //             break;
            //         }
            //         ecs::Entity &e = this->_world.getEntityById(this->_world.getCurrentScene(), id);
            //         auto &velocity = this->_world.get<ecs::Velocity>(e);

            //         if (direction == "left") {
            //             velocity.dx = -4;
            //         } else if (direction == "right") {
            //             velocity.dx = 4;
            //         } else if (direction == "up") {
            //             velocity.dy = -4;
            //         } else if (direction == "down") {
            //             velocity.dy = 4;
            //         } else if (direction == "stopx") {
            //             velocity.dx = 0;
            //         } else if (direction == "stopy") {
            //             velocity.dy = 0;
            //         }

            //         for (auto &player : _players) {
            //             if (player.getEndpoint() != buffer.getEndpoint()) {
            //                 send(buffer, player.getEndpoint());
            //             }
            //         }
            //         break;
            //     }
            //     case ecs::MessageType::PLAYER_SHOOT:
            //     {
            //         std::size_t id = 0;

            //         try {
            //             id = std::stoi(messageString);
            //         } catch (std::exception &e) {
            //             std::cerr << "Exception in processMessages: " << e.what() << std::endl;
            //             break;
            //         }

            //         ecs::Entity &e = this->_world.getEntityById(this->_world.getCurrentScene(), id);
            //         auto &position = this->_world.get<ecs::Position>(e);
            //         auto &sprite = this->_world.get<ecs::Sprite>(e);
            //         auto &scale = this->_world.get<ecs::Scale>(e);

            //         entityTemplate.playerBullet(this->_world, "", static_cast<int>(position.x + sprite.source.width * scale.x), static_cast<int>(position.y + (sprite.source.height * scale.y) / 2));

            //         for (auto &player : _players) {
            //             send(buffer, player.getEndpoint());
            //         }
            //         break;
            //     }
            //     case ecs::MessageType::PLAYER_DISCONNECTED:
            //     {
            //         for (auto &player : _players) {
            //             if (player.getEndpoint() != buffer.getEndpoint()) {
            //                 ecs::Buffer newBuffer;
            //                 newBuffer.writeMessageType(ecs::MessageType::PLAYER_DISCONNECTED);
            //                 newBuffer.writeString(messageString);
            //                 send(newBuffer, player.getEndpoint());
            //             }
            //         }

            //         for (auto it = _players.begin(); it != _players.end(); ++it) {
            //             if ((*it).getEndpoint() == buffer.getEndpoint()) {
            //                 _players.erase(it);
            //                 break;
            //             }
            //         }
            //         break;
            //     }
            //     default:
            //         break;
            // }

    void Server::receive(ecs::Message &message) {
        std::vector<char> buffer(1024);
        asio::ip::udp::endpoint sender_endpoint;

        std::size_t length = this->_socket->receive_from(asio::buffer(buffer), sender_endpoint);

        if (length >= sizeof(std::size_t) + sizeof(ecs::MessageType)) {
            std::size_t dataSize;
            ecs::MessageType messageType;
            std::memcpy(&dataSize, buffer.data(), sizeof(dataSize));
            std::memcpy(&messageType, buffer.data() + sizeof(dataSize), sizeof(messageType));

            message.setMessageType(messageType);

            if (length >= sizeof(dataSize) + sizeof(messageType)) {
                std::vector<char> messageData(buffer.begin() + sizeof(dataSize) + sizeof(messageType), 
                                                buffer.begin() + sizeof(dataSize) + sizeof(messageType) + dataSize);
                message.setMessageData(messageData);
            }
            message.setEndpoint(sender_endpoint);
        }
    }

    void Server::sendGameState()
    {
        this->mutex.lock();
        ecs::EntityList entityList;

        for (auto &entity : _world.getCurrentScene().entities) {
                ecs::Position &posSpaceship = _world.get<ecs::Position>(entity);
                ecs::SceneManager &scenemanager = _world.getSceneManager();
                ecs::EntityInfo entityInfo;
                if (scenemanager.has<ecs::Shooter>(entity)) {
                    entityInfo.entityType = ecs::EntityType::Player;
                    std::cout << "player" << std::endl;
                }
                else if (scenemanager.has<ecs::Damage>(entity) && !scenemanager.has<ecs::Shooter>(entity)) {
                    entityInfo.entityType = ecs::EntityType::Missile;
                    std::cout << "Missile" << std::endl;
                } else if (scenemanager.has<ecs::Name>(entity) && !scenemanager.has<ecs::Controllable>(entity)) {
                    entityInfo.entityType = ecs::EntityType::Ennemy;
                    std::cout << "Ennemy" << std::endl;
                }
                entityInfo.id = entity.id;
                entityInfo.hp = 0;
                entityInfo.pos = {posSpaceship.x, posSpaceship.y};
                entityList.entityList.push_back(entityInfo);
        }
        
        for (auto &player : _players) {
                send(entityList, ecs::MessageType::EntityList, player.getEndpoint());
        }
        this->mutex.unlock();
    }
}
