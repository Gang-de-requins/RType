#include "Player.hpp"
#include "World.hpp"

namespace rtype {
    Player::Player(ecs::Entity &Entityspaceship, const std::string &name) :
    m_spaceship(Entityspaceship),
    c_name(name)
    {
    }

    Player::~Player()
    {
    }

    ecs::Entity &Player::getSpaceship()
    {
        return this->m_spaceship;
    }
}
