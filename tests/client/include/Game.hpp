#ifndef GAME_HPP
#define GAME_HPP

#include <unordered_map>
#include "raylib.h"
#include "GameEngine.hpp"
#include "Network.hpp"
#include "Player.hpp"

#define SCENE_MENU 0
#define SCENE_GAME 1
#define SCENE_GAME_OVER 2

namespace rtype {
    class Game {
        ecs::World m_world;
        Network m_network;
        std::vector<Player> m_players;

        public:
            Game();
            ~Game();
            void run();
            ecs::World &getWorld();
            float getOffsetColorSpaceship() const;
            void addPlayer(Player &player);
            std::vector<Player> &getPlayers();

        private:
            void initScenes();
    };
}

#endif /* GAME_HPP */
