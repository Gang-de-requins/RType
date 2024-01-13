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
