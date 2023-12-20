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

namespace ecs {
    class World;
}

namespace rtype {
    class Game;

    class Player {
        ecs::Entity &m_spaceship;
        const std::string c_name;
        bool m_isMovingTop;
        bool m_isMovingBottom;
        bool m_isMovingLeft;
        bool m_isMovingRight;

        public:
            Player(ecs::Entity &Entityspaceship, const std::string &name);
            ~Player();
            ecs::Entity &getSpaceshipEntity();
            const std::string &getName() const;
            void move(Game &game, ::Network::MessageType direction);
            void shoot(Game &game);
        
        private:
            void stopMoving(ecs::Acceleration &accSpaceship);
    };
}

#endif /* GAME_PLAYER_HPP */
