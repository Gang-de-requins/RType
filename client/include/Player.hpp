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
        std::size_t m_id;
        const std::string c_name;
        bool m_isMovingTop;
        bool m_isMovingBottom;
        bool m_isMovingLeft;
        bool m_isMovingRight;
        bool m_isAlive;

        public:
            Player(ecs::Entity &Entityspaceship, const std::string &name);
            ~Player();
            std::size_t getId() const;

            const std::string &getName() const;
            void move(Game &game, std::string msg);
            void shoot(Game &game);
            void setAlive(bool alive);
        
        private:
            void stopMoving(ecs::Acceleration &accSpaceship);
    };
}

#endif /* GAME_PLAYER_HPP */
