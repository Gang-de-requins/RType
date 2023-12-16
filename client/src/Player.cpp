#include "Player.hpp"
#include "Game.hpp"

namespace rtype {
    Player::Player(ecs::Entity &Entityspaceship, ecs::Entity &Entityname, const std::string &name) :
    m_spaceship(Entityspaceship),
    m_name(Entityname),
    c_name(name),
    m_isMoving(false)
    {
    }

    Player::~Player()
    {
    }

    ecs::Entity &Player::getSpaceshipEntity()
    {
        return this->m_spaceship;
    }

    ecs::Entity &Player::getNameEntity()
    {
        return this->m_name;
    }

    const std::string &Player::getName() const
    {
        return this->c_name;
    }

    void Player::move(Game &game, ::Network::MessageType direction)
    {
        ecs::World &world = game.getWorld();
        ecs::Acceleration &accSpaceship = world.get<ecs::Acceleration>(this->m_spaceship);
        ecs::Acceleration &accName = world.get<ecs::Acceleration>(this->m_name);

        switch (direction) {
            case ::Network::MessageType::GoTop:
                this->m_isMoving = true;
                accSpaceship.ddx = 0;
                accSpaceship.ddy = -0.3f;
                accSpaceship.maxSpeed = 4.0f;
                accName.ddx = 0;
                accName.ddy = -0.3f;
                accName.maxSpeed = 4.0f;
                break;
            case ::Network::MessageType::GoBottom:
                this->m_isMoving = true;
                accSpaceship.ddx = 0;
                accSpaceship.ddy = 0.3f;
                accSpaceship.maxSpeed = 4.0f;
                accName.ddx = 0;
                accName.ddy = 0.3f;
                accName.maxSpeed = 4.0f;
                break;
            case ::Network::MessageType::GoLeft:
                this->m_isMoving = true;
                accSpaceship.ddx = -0.3f;
                accSpaceship.ddy = 0;
                accSpaceship.maxSpeed = 4.0f;
                accName.ddx = -0.3f;
                accName.ddy = 0;
                accName.maxSpeed = 4.0f;
                break;
            case ::Network::MessageType::GoRight:
                this->m_isMoving = true;
                accSpaceship.ddx = 0.3f;
                accSpaceship.ddy = 0;
                accSpaceship.maxSpeed = 4.0f;
                accName.ddx = 0.3f;
                accName.ddy = 0;
                accName.maxSpeed = 4.0f;
                break;
            default:
                this->m_isMoving = false;
                std::thread stopThread(&Player::stopMoving, this, std::ref(accSpaceship), std::ref(accName));
                stopThread.detach();
                break;
        }
    }

    void Player::stopMoving(ecs::Acceleration &accSpaceship, ecs::Acceleration &accName)
    {
        std::mutex mutex;

        while (!this->m_isMoving && accSpaceship.maxSpeed > 0.0f && accName.maxSpeed > 0.0f) {
            std::unique_lock<std::mutex> lock(mutex);
            accSpaceship.ddx *= -1;
            accSpaceship.ddy *= -1;
            accName.ddx *= -1;
            accName.ddy *= -1;

            accSpaceship.maxSpeed -= 0.1f;
            accSpaceship.maxSpeed = std::max(accSpaceship.maxSpeed, 0.0f);
            accName.maxSpeed -= 0.1f;
            accName.maxSpeed = std::max(accName.maxSpeed, 0.0f);
            lock.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(15));
        }
    }
}
