#ifndef GAME_PLAYER_HPP
#define GAME_PLAYER_HPP

#include <string>
#include <utility>
#include "Entity.hpp"

namespace ecs {
    class World;
}

namespace rtype {
    class Player {
        ecs::Entity m_spaceship;
        const std::string c_name;
        public:
            Player(ecs::Entity &Entityspaceship, const std::string &name);
            ~Player();
            ecs::Entity &getSpaceship();
    };
}

#endif /* GAME_PLAYER_HPP */
