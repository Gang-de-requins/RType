#ifndef GAME_HPP
#define GAME_HPP

#include <unordered_map>
#include "GameEngine.hpp"
#include "Network.hpp"
#include "Player.hpp"
#include "raylib.h"

#define SCENE_MENU 0
#define SCENE_SETTINGS 1
#define SCENE_CHOOSENAME 2
#define SCENE_GAME 3

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
            void loadMenu(ecs::Scene &scene);
            void loadSettings(ecs::Scene &scene);
            void loadChooseName(ecs::Scene &scene);
            void loadGame(ecs::Scene &scene);
    };
}

#endif /* GAME_HPP */
