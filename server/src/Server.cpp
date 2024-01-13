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