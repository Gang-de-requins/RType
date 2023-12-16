#ifndef GAME_PLAYER_HPP
#define GAME_PLAYER_HPP

#include <string>
#include "Entity.hpp"

namespace rtype {
    class Player {
        ecs::Entity m_spaceship;
        ecs::Entity m_name;
        const std::string c_name;

        public:
            Player(ecs::Entity &Entityspaceship, ecs::Entity &Entityname, const std::string &name);
            ~Player();
            ecs::Entity &getSpaceship();
            ecs::Entity &getName();
    };
}

#endif /* GAME_PLAYER_HPP */
