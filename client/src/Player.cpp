#include "Player.hpp"

namespace rtype {
    Player::Player(ecs::Entity &Entityspaceship, ecs::Entity &Entityname, const std::string &name) :
    m_spaceship(Entityspaceship),
    m_name(Entityname),
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

    ecs::Entity &Player::getName()
    {
        return this->m_name;
    }
}
