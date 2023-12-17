#include "Player.hpp"
#include "Game.hpp

namespace rtype {
    Player::Player(ecs::Entity &Entityspaceship, const std::string &name) :
    m_spaceship(Entityspaceship),
    c_name(name),
    m_isMovingTop(false),
    m_isMovingBottom(false),
    m_isMovingLeft(false),
    m_isMovingRight(false)
    {
    }

    Player::~Player()
    {
    }

    ecs::Entity &Player::getSpaceshipEntity()
    {
        return this->m_spaceship;
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
        std::thread stopThread;

        switch (direction) {
            case ::Network::MessageType::GoTop:
                this->m_isMovingTop = true;
                accSpaceship.ddx = 0;
                accSpaceship.ddy = -0.3f;
                accSpaceship.maxSpeed = 4.0f;
                accName.ddx = 0;
                accName.ddy = -0.3f;
                accName.maxSpeed = 4.0f;
                break;
            case ::Network::MessageType::GoBottom:
                this->m_isMovingBottom = true;
                accSpaceship.ddx = 0;
                accSpaceship.ddy = 0.3f;
                accSpaceship.maxSpeed = 4.0f;
                accName.ddx = 0;
                accName.ddy = 0.3f;
                accName.maxSpeed = 4.0f;
                break;
            case ::Network::MessageType::GoLeft:
                this->m_isMovingLeft = true;
                accSpaceship.ddx = -0.3f;
                accSpaceship.ddy = 0;
                accSpaceship.maxSpeed = 4.0f;
                accName.ddx = -0.3f;
                accName.ddy = 0;
                accName.maxSpeed = 4.0f;
                break;
            case ::Network::MessageType::GoRight:
                this->m_isMovingRight = true;
                accSpaceship.ddx = 0.3f;
                accSpaceship.ddy = 0;
                accSpaceship.maxSpeed = 4.0f;
                accName.ddx = 0.3f;
                accName.ddy = 0;
                accName.maxSpeed = 4.0f;
                break;
            case ::Network::MessageType::StopTop:
                this->m_isMovingTop = false;
                stopThread = std::thread(&Player::stopMoving, this, std::ref(accSpaceship), std::ref(accName));
                stopThread.detach();
                break;
            case ::Network::MessageType::StopBottom:
                this->m_isMovingBottom = false;
                stopThread = std::thread(&Player::stopMoving, this, std::ref(accSpaceship), std::ref(accName));
                stopThread.detach();
                break;
            case ::Network::MessageType::StopLeft:
                this->m_isMovingLeft = false;
                stopThread = std::thread(&Player::stopMoving, this, std::ref(accSpaceship), std::ref(accName));
                stopThread.detach();
                break;
            case ::Network::MessageType::StopRight:
                this->m_isMovingRight = false;
                stopThread = std::thread(&Player::stopMoving, this, std::ref(accSpaceship), std::ref(accName));
                stopThread.detach();
                break;
            default:
                break;
        }
    }

    void Player::stopMoving(ecs::Acceleration &accSpaceship, ecs::Acceleration &accName)
    {
        std::mutex mutex;

        while (!this->m_isMovingTop && !this->m_isMovingBottom && !this->m_isMovingLeft && !this->m_isMovingRight) {
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
