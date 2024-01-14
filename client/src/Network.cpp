/*
** EPITECH PROJECT, 2024
** RType [WSL : Ubuntu]
** File description:
** Network
*/

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
        ecs::PlayerJoined myStruct1ToSend = {playerName};
        this->send(myStruct1ToSend, ecs::MessageType::PlayerJoined);
        this->m_connected = true;
    }

    template <typename T>
    void Network::send(T& data, ecs::MessageType messageType) {
        std::vector<char> serializedData = data.serialize();
        std::size_t dataSize = serializedData.size();

        std::vector<char> packet(sizeof(std::size_t) + sizeof(ecs::MessageType) + dataSize);
        std::memcpy(packet.data(), &dataSize, sizeof(dataSize));
        std::memcpy(packet.data() + sizeof(dataSize), &messageType, sizeof(messageType));
        std::memcpy(packet.data() + sizeof(dataSize) + sizeof(ecs::MessageType), serializedData.data(), dataSize);

        this->m_socket.send_to(asio::buffer(packet), this->m_endpoint);
    }

template void Network::send<ecs::Move>(ecs::Move&, ecs::MessageType);

    void Network::receive(Game &game)
    {
        while (this->m_running) {
            try {
                std::array<char, 20000> receiveBuffer;
                asio::ip::udp::endpoint senderEndpoint;

                std::size_t bytes_transferred = this->m_socket.receive_from(asio::buffer(receiveBuffer), senderEndpoint);

                if (bytes_transferred >= sizeof(std::size_t) + sizeof(ecs::MessageType)) {
                    ecs::Message message;
                    std::size_t dataSize;
                    ecs::MessageType messageType;
                    std::memcpy(&dataSize, receiveBuffer.data(), sizeof(dataSize));
                    std::memcpy(&messageType, receiveBuffer.data() + sizeof(dataSize), sizeof(messageType));

                    message.setMessageType(messageType);

                    if (bytes_transferred >= sizeof(dataSize) + sizeof(messageType)) {
                        std::vector<char> messageData(receiveBuffer.begin() + sizeof(dataSize) + sizeof(messageType), 
                                receiveBuffer.begin() + sizeof(dataSize) + sizeof(messageType) + dataSize);
                        message.setMessageData(messageData);
                    }
                    if (message.getMessageType() == ecs::MessageType::Loose) {
                        ecs::NewPlayer receivedStruct;
                        receivedStruct.deserialize(message.getMessageData());
                        std::cout << "Loose" << std::endl;
                    }
                    if (message.getMessageType() == ecs::MessageType::Win) {
                        ecs::NewPlayer receivedStruct;
                        receivedStruct.deserialize(message.getMessageData());
                        std::cout << "win" << std::endl;
                    }
                    if (message.getMessageType() == ecs::MessageType::PlayerJoinedAccept) {
                        ecs::NewPlayer receivedStruct;
                        receivedStruct.deserialize(message.getMessageData());
                        std::cout << "You have joined the game with the name: " << receivedStruct.playername
                        << " and with the id: " << receivedStruct.id <<std::endl;
                        this->newPlayerConnected(game, receivedStruct, true);
                    }

                    if (message.getMessageType() == ecs::MessageType::NewPlayer) {
                        ecs::NewPlayer receivedStruct;
                        receivedStruct.deserialize(message.getMessageData());
                        std::cout << "New player with name :" << receivedStruct.playername
                        << " and with the id: " << receivedStruct.id << " has joined the game" << std::endl;
                        this->newPlayerConnected(game, receivedStruct, false);
                    } 
                    if (message.getMessageType() == ecs::MessageType::NewEnemy) {
                        ecs::NewPlayer receivedStruct;
                        receivedStruct.deserialize(message.getMessageData());
                        std::cout << "New Enemy with the id: " << receivedStruct.id << " has spawned." << std::endl;
                        this->newEnemy(game, receivedStruct);
                    } 
                    if (message.getMessageType() == ecs::MessageType::EntityList) {
                        ecs::EntityList receivedStruct;
                        receivedStruct.deserialize(message.getMessageData());
                        ecs::World &world = game.getWorld();

                        std::cout << "Entity List Received:" << std::endl;
                        for (auto& entityInfo : receivedStruct.entityList) {
                                    if (entityInfo.entityType == ecs::EntityType::Player) {
                                        std::cout << "Player with ";

                                        if (world.hasEntity(world.getCurrentScene(), entityInfo.id)) {
                                            std::cout << "Entity ID: " << entityInfo.id << " already exists" << std::endl;
                                            ecs::Entity &e = world.getEntityById(world.getCurrentScene(), entityInfo.id);
                                            ecs::Position &pos = world.get<ecs::Position>(e);
                                            pos.x = entityInfo.pos.first;
                                            pos.y = entityInfo.pos.second;
                                        } else {
                                            std::cout << "Entity ID: " << entityInfo.id << " does not exist, creating it" << std::endl;
                                            ecs::NewPlayer newPlayer = {game.getPlayerName(), static_cast<std::size_t>(entityInfo.id), {entityInfo.pos.first, entityInfo.pos.second}, entityInfo.hp};
                                            this->newPlayerConnected(game, newPlayer, false);
                                        }
                                    } else if (entityInfo.entityType == ecs::EntityType::Missile) {
                                        std::cout << "Missile with ";

                                        if (world.hasEntity(world.getCurrentScene(), entityInfo.id)) {
                                            std::cout << "Entity ID: " << entityInfo.id << " already exists" << std::endl;
                                            ecs::Entity &e = world.getEntityById(world.getCurrentScene(), entityInfo.id);
                                            ecs::Position &pos = world.get<ecs::Position>(e);
                                            pos.x = entityInfo.pos.first;
                                            pos.y = entityInfo.pos.second;
                                        } else {
                                            std::cout << "Entity ID: " << entityInfo.id << " does not exist, creating it" << std::endl;
                                            this->newMissile(game, entityInfo);
                                        }

                                    }   else if (entityInfo.entityType == ecs::EntityType::Ennemy) {
                                        std::cout << "Ennemy with ";

                                        std::cout << "Entity ID: " << entityInfo.id << std::endl;
                                        if (world.hasEntity(world.getCurrentScene(), entityInfo.id)) {
                                            std::cout << "Entity ID: " << entityInfo.id << " already exists" << std::endl;
                                            ecs::Entity &e = world.getEntityById(world.getCurrentScene(), static_cast<std::size_t>(entityInfo.id));
                                            ecs::Position &pos = world.get<ecs::Position>(e);
                                            pos.x = entityInfo.pos.first;
                                            pos.y = entityInfo.pos.second;
                                        } else {
                                            std::cout << "Entity ID: " << entityInfo.id << " does not exist, creating it" << std::endl;
                                            ecs::NewPlayer newPlayer = {"enemy", static_cast<std::size_t>(entityInfo.id), {entityInfo.pos.first, entityInfo.pos.second}, entityInfo.hp};
                                            this->newEnemy(game, newPlayer);
                                        }
                                    }
                            std::cout << "Entity ID: " << entityInfo.id 
                                    << ", HP: " << entityInfo.hp 
                                    << ", Position: (" << entityInfo.pos.first 
                                    << ", " << entityInfo.pos.second << ")" << std::endl;
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

    //                     switch (messageType) {
    //                         case ecs::MessageType::PLAYER_CONNECTED:
    //                             std::cout << "New player connected: " << msg << std::endl;
    //                             this->newPlayerConnected(game, msg);
    //                             break;
    //                         case ecs::MessageType::PLAYER_DISCONNECTED:
    //                             std::cout << "Player disconnected: " << msg << std::endl;
    //                             this->playerDisconnected(game, msg);
    //                             break;
    //                         case ecs::MessageType::PLAYER_MOVE:
    //                             std::cout << "Player move: " << msg << std::endl;
    //                             this->moveEntity(game, msg);
    //                             break;
    //                         case ecs::MessageType::PLAYER_SHOOT:
    //                             std::cout << "Player shoot: " << msg << std::endl;
    //                             this->newMissile(game, msg);
    //                             break;
    //                         case ecs::MessageType::ENEMY_SPAWN:
    //                             std::cout << "Enemy spawn: " << msg << std::endl;
    //                             this->newEnemy(game, msg);
    //                             break;
    //                         case ecs::MessageType::ENEMY_SHOOT:
    //                             break;
    //                         case ecs::MessageType::ENTITY_DESTROYED:
    //                             this->playerDisconnected(game, msg);
    //                             break;
    //                         default:
    //                             break;
    //                     }
    //                 }
    //             }
    //         } catch (const std::exception &e) {
    //             std::cerr << "Error: " << e.what() << std::endl;
    //         }
    //     }
    //     std::cout << "Stopped receiving messages" << std::endl;
    // }

    void Network::setRunning(bool running)
    {
        this->m_running = running;
    }

    bool Network::isConnected() const
    {
        return this->m_connected;
    }

    /* ---------------------------- PRIVATE FUNCTIONS --------------------------- */

    void Network::newPlayerConnected(Game &game, ecs::NewPlayer& newPlayer, bool isMe)
    {
        std::cout << "New player connected: " << newPlayer.playername << std::endl;
        auto &world = game.getWorld();

        ecs::Scene &inGame = game.getWorld().getCurrentScene();
        ecs::Entity &player = game.getWorld().createEntityWithId(inGame, newPlayer.id);

        world.assign(player, ecs::Position{newPlayer.pos.first, newPlayer.pos.second});
        world.assign(player, ecs::Velocity{0, 0});
        world.assign(player, ecs::Sprite{"assets/characters2.gif", ecs::Rectangle{0, 0, 32, 32}, ecs::Vector2{0, 0}});
        world.assign(player, ecs::Acceleration{0, 0, 4});
        world.assign(player, ecs::Scale{1, 1});
        world.assign(player, ecs::Rotation{0});
        world.assign(player, ecs::Name{newPlayer.playername, ecs::Position{-20, -20}});
        world.assign(player, ecs::Collision{false, {}, true});
        world.assign(player, ecs::Animation{ecs::Rectangle{0, 0, 32, 0}, 8, 0, 150, std::chrono::steady_clock::now()});
        world.assign(player, ecs::Health{static_cast<float>(newPlayer.hp)});

        if (isMe) {
            // world.assign(player, ecs::Controllable{
            //     std::unordered_map<int, std::tuple<ecs::ActionTrigger, std::function<void(ecs::SceneManager & sceneManager, ecs::Scene & scene, ecs::Entity * entity)>>> {
            //         {KEY_UP, std::make_tuple<ecs::ActionTrigger, std::function<void(ecs::SceneManager&, ecs::Scene&, ecs::Entity*)>>(
            //             ecs::ActionTrigger::Hold, [](ecs::SceneManager& sceneManager, ecs::Scene& scene, ecs::Entity* entity) {
            //                 static_cast<void>(sceneManager);

            //                 scene.events[ecs::EventType::Input].push_back({
            //                     ecs::GameEvent::MoveUp,
            //                     {entity}
            //                 });
            //             }
            //         )},
            //         {KEY_DOWN, std::make_tuple<ecs::ActionTrigger, std::function<void(ecs::SceneManager&, ecs::Scene&, ecs::Entity*)>>(
            //             ecs::ActionTrigger::Hold, [](ecs::SceneManager& sceneManager, ecs::Scene& scene, ecs::Entity* entity) {
            //                 static_cast<void>(sceneManager);

            //                 scene.events[ecs::EventType::Input].push_back({
            //                     ecs::GameEvent::MoveDown,
            //                     {entity}
            //                 });
            //             }
            //         )},
            //         {KEY_LEFT, std::make_tuple<ecs::ActionTrigger, std::function<void(ecs::SceneManager&, ecs::Scene&, ecs::Entity*)>>(
            //             ecs::ActionTrigger::Hold, [](ecs::SceneManager& sceneManager, ecs::Scene& scene, ecs::Entity* entity) {
            //                 static_cast<void>(sceneManager);

            //                 scene.events[ecs::EventType::Input].push_back({
            //                     ecs::GameEvent::MoveLeft,
            //                     {entity}
            //                 });
            //             }
            //         )},
            //         {KEY_RIGHT, std::make_tuple<ecs::ActionTrigger, std::function<void(ecs::SceneManager&, ecs::Scene&, ecs::Entity*)>>(
            //             ecs::ActionTrigger::Hold, [](ecs::SceneManager& sceneManager, ecs::Scene& scene, ecs::Entity* entity) {
            //                 static_cast<void>(sceneManager);

            //                 scene.events[ecs::EventType::Input].push_back({
            //                     ecs::GameEvent::MoveRight,
            //                     {entity}
            //                 });
            //             }
            //         )},
            //         {KEY_SPACE, std::make_tuple<ecs::ActionTrigger, std::function<void(ecs::SceneManager&, ecs::Scene&, ecs::Entity*)>>(
            //             ecs::ActionTrigger::Press, [](ecs::SceneManager& sceneManager, ecs::Scene& scene, ecs::Entity* entity) {
            //                 if (sceneManager.has<ecs::Shooter>(*entity)) {
            //                     ecs::Shooter& shooter = sceneManager.get<ecs::Shooter>(*entity);

            //                     if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - shooter.lastShotTime) >= shooter.cooldown) {
            //                         shooter.lastShotTime = std::chrono::steady_clock::now();
            //                         scene.events[ecs::EventType::Spawn].push_back({
            //                             ecs::GameEvent::SpawnPlayerBullet,
            //                             {entity}
            //                         });
            //                     }
            //                 }
            //             }
            //         )},
            //     }
            // });
            game.setId(player.id);
        }

        Player nPlayer(player, newPlayer.playername);

        game.addPlayer(nPlayer);
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

    void Network::newMissile(Game &game, ecs::EntityInfo &entityInfo)
    {
        auto &world = game.getWorld();
        ecs::Scene &inGame = world.getCurrentScene();

        ecs::Entity &missile = world.createEntityWithId(inGame, entityInfo.id);
        world.assign(missile, ecs::Position{entityInfo.pos.first, entityInfo.pos.second});
        // world.assign(missile, ecs::Velocity{0, 0});
        world.assign(missile, ecs::Sprite{"assets/28.png", ecs::Rectangle{0, 0, 210, 92}, ecs::Vector2{0, 0}});
        world.assign(missile, ecs::Scale{0.25, 0.25});
        world.assign(missile, ecs::Rotation{0});
        // world.assign(missile, ecs::Name{"missile", ecs::Position{-20, -20}});
        // world.assign(missile, ecs::Collision{false, {}, true});
        // world.assign(missile, ecs::Damage{30});
    }

    void Network::newEnemy(Game &game, ecs::NewPlayer& newPlayer)
    {
        auto &world = game.getWorld();
        ecs::Scene &inGame = world.getCurrentScene();

        ecs::Entity &enemy = world.createEntityWithId(inGame, newPlayer.id);
        world.assign(enemy, ecs::Position{newPlayer.pos.first, newPlayer.pos.second});
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
