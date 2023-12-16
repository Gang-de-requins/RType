#ifndef GAME_PLAYER_HPP
#define GAME_PLAYER_HPP

#include <string>
#include <thread>
#include <mutex>
#include "Entity.hpp"
#include "Network.hpp"

namespace ecs {
    struct Acceleration;
}

namespace rtype {
    class Game;

    class Player {
        ecs::Entity &m_spaceship;
        ecs::Entity &m_name;
        const std::string c_name;
        bool m_isMoving;

        public:
            Player(ecs::Entity &Entityspaceship, ecs::Entity &Entityname, const std::string &name);
            ~Player();
            ecs::Entity &getSpaceshipEntity();
            ecs::Entity &getNameEntity();
            const std::string &getName() const;
            void move(Game &game, ::Network::MessageType direction);
        
        private:
            void stopMoving(ecs::Acceleration &accSpaceship, ecs::Acceleration &accName);
    };
}

#endif /* GAME_PLAYER_HPP */
