#include "Player.hpp"
#include "Game.hpp"

namespace rtype {
    Player::Player(ecs::Entity &Entityspaceship, const std::string &name) :
    m_id(Entityspaceship.id),
    c_name(name),
    m_isMovingTop(false),
    m_isMovingBottom(false),
    m_isMovingLeft(false),
    m_isMovingRight(false),
    m_isAlive(true)
    {
    }

    Player::~Player()
    {
    }

    std::size_t Player::getId() const
    {
        return this->m_id;
    }

    const std::string &Player::getName() const
    {
        return this->c_name;
    }

    void Player::move(Game &game, std::string msg)
    {
        ecs::World &world = game.getWorld();

        // direction is id:direction
        std::string delimiter = ":";
        std::string rawId = msg.substr(0, msg.find(delimiter));
        std::string direction = msg.substr(msg.find(delimiter) + 1, msg.length());
        std::size_t id = std::stoi(rawId);
        ecs::Entity &e = world.getEntityById(world.getCurrentScene(), id);
        ecs::Velocity &velocity = world.get<ecs::Velocity>(e);

        if (direction == "up") {
            this->m_isMovingTop = true;
            velocity.dy = -4.0f;
        } else if (direction == "down") {
            this->m_isMovingBottom = true;
            velocity.dy = 4.0f;
        } else if (direction == "left") {
            this->m_isMovingLeft = true;
            velocity.dx = -4.0f;
        } else if (direction == "right") {
            this->m_isMovingRight = true;
            velocity.dx = 4.0f;
        } else if (direction == "stopy") {
            this->m_isMovingTop = false;
            velocity.dy = 0;
        } else if (direction == "stopx") {
            this->m_isMovingLeft = false;
            velocity.dx = 0;
        }
    }

    void Player::shoot(Game &game)
    {
        ecs::World &world = game.getWorld();
        ecs::SceneManager &sceneManager = world.getSceneManager();
        ecs::Entity &e = world.getEntityById(world.getCurrentScene(), this->m_id);
        ecs::Position &position = world.get<ecs::Position>(e);
        ecs::Sprite &sprite = world.get<ecs::Sprite>(e);
        ecs::Scale &scale = world.get<ecs::Scale>(e);

        ecs::Entity &missile = world.createEntity(world.getCurrentScene());
        world.assign(missile, ecs::Position{position.x + sprite.source.width * scale.x, position.y + (sprite.source.height * scale.y) / 2});
        world.assign(missile, ecs::Velocity{0, 0});
        world.assign(missile, ecs::Sprite{"assets/28.png", ecs::Rectangle{0, 0, 210, 92}, ecs::Vector2{0, 0}});
        world.assign(missile, ecs::Acceleration{1, 0, 15});
        world.assign(missile, ecs::Scale{0.25, 0.25});
        world.assign(missile, ecs::Rotation{0});
        world.assign(missile, ecs::Collision{false, {}, true});
        world.assign(missile, ecs::Sound{"assets/weird.wav"});
        world.assign(missile, ecs::Damage{10});

        Sound &sound = sceneManager.getSound("assets/weird.wav");
        
        PlaySound(sound);
    }

    void Player::setAlive(bool alive)
    {
        this->m_isAlive = alive;
    }

    void Player::stopMoving(ecs::Acceleration &accSpaceship)
    {
        std::mutex mutex;

        while (!this->m_isMovingTop && !this->m_isMovingBottom && !this->m_isMovingLeft && !this->m_isMovingRight) {
            std::unique_lock<std::mutex> lock(mutex);
            accSpaceship.ddx *= -1;
            accSpaceship.ddy *= -1;

            accSpaceship.maxSpeed -= 0.1f;
            accSpaceship.maxSpeed = std::max(accSpaceship.maxSpeed, 0.0f);
            lock.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(15));
        }
    }
}
