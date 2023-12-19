#include "Server.hpp"

namespace rtype {
    Server::Server(const unsigned short port) :
    c_port(port),
    m_udpServer(this->m_io_context, port, this->m_world)
    {
        ecs::Scene &inGame = this->m_world.createScene();
        ecs::Entity &spaceBackground = this->m_world.createEntity(inGame);

        this->m_world.assign(spaceBackground, ecs::Position{0, 0});
        this->m_world.assign(spaceBackground, ecs::Sprite{"./assets/parallax-space-background.png", ecs::Rectangle{0, 0, 272, 160}, ecs::Vector2{0, 0}});
        this->m_world.assign(spaceBackground, ecs::Velocity{0, 0});
        this->m_world.assign(spaceBackground, ecs::Acceleration{0, 0, 4});
        this->m_world.assign(spaceBackground, ecs::Scale{14, 6});
        this->m_world.assign(spaceBackground, ecs::Rotation{0});

        ecs::Entity &planetBackground = this->m_world.createEntity(inGame);
        this->m_world.assign(planetBackground, ecs::Position{0, 0});
        this->m_world.assign(planetBackground, ecs::Sprite{"./assets/parallax-space-big-planet.png", ecs::Rectangle{0, 0, 88, 87}, ecs::Vector2{0, 0}});
        this->m_world.assign(planetBackground, ecs::Velocity{0, 0});
        this->m_world.assign(planetBackground, ecs::Acceleration{0, 0, 5});
        this->m_world.assign(planetBackground, ecs::Scale{2, 2});
        this->m_world.assign(planetBackground, ecs::Rotation{0});

        ecs::Entity &planets = this->m_world.createEntity(inGame);
        this->m_world.assign(planets, ecs::Position{0, 0});
        this->m_world.assign(planets, ecs::Sprite{"./assets/parallax-space-far-planets.png", ecs::Rectangle{0, 0, 272, 160}, ecs::Vector2{0, 0}});
        this->m_world.assign(planets, ecs::Velocity{0, 0});
        this->m_world.assign(planets, ecs::Acceleration{0, 0, 6});
        this->m_world.assign(planets, ecs::Scale{2, 2});
        this->m_world.assign(planets, ecs::Rotation{0});
    }

    Server::~Server()
    {
    }

    void Server::run()
    {
        this->m_io_context.run();
    }
}
