#ifndef GAME_HPP
#define GAME_HPP

#include <unordered_map>
#include "GameEngine.hpp"
#include "Network.hpp"
#include "Player.hpp"
#include "raylib.h"

#define SCENE_MENU 0
#define SCENE_GAME 1
#define SCENE_GAME_OVER 2

namespace rtype {
    class Game {
        ecs::World m_world;
        Network m_network;
        std::vector<Player> m_players;
        std::string m_playerName;

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
