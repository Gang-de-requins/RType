#include "Game.hpp"

namespace rtype {
    Game::Game()
    {
        initScenes();
        this->m_network.m_ip = "127.0.0.1";
        this->m_network.m_port = 4444;
        this->m_playerName = "Name";
    }

    Game::~Game()
    {
    }

    void Game::run()
    {
        SetTraceLogLevel(LOG_NONE);
        InitAudioDevice();
        InitWindow(1920, 1080, "rtype");
        SetTargetFPS(60);
        this->m_world.loadTextures({ "assets/characters.gif" });

        while (!WindowShouldClose())
        {
            if (IsKeyPressed(KEY_UP))
                this->m_network.send(ecs::MessageType::GoTop, this->m_playerName);
            if (IsKeyPressed(KEY_DOWN))
                this->m_network.send(ecs::MessageType::GoBottom, this->m_playerName);
            if (IsKeyPressed(KEY_LEFT))
                this->m_network.send(ecs::MessageType::GoLeft, this->m_playerName);
            if (IsKeyPressed(KEY_RIGHT))
                this->m_network.send(ecs::MessageType::GoRight, this->m_playerName);
            if (IsKeyPressed(KEY_SPACE)) {
            }

            BeginDrawing();
            ClearBackground(BLACK);

            this->m_world.update();

            EndDrawing();
        }

        CloseWindow();
        CloseAudioDevice();
        this->m_network.setRunning(false);
    }

    ecs::World &Game::getWorld()
    {
        return this->m_world;
    }

    float Game::getOffsetColorSpaceship() const
    {
        return static_cast<float>(this->m_players.size() * 16);
    }

    void Game::addPlayer(Player &player)
    {
        this->m_players.push_back(player);
    }

    std::vector<Player> &Game::getPlayers()
    {
        return this->m_players;
    }

    /* ---------------------------- PRIVATE FUNCTIONS --------------------------- */

    void Game::initScenes()
    {

        /* ------------------------- Scene InMenu --------------------------------*/

        ecs::Scene &inMenu = this->m_world.createScene();

        loadMenu(inMenu);

        /* ------------------------- Scene InSettings--------------------------------*/

        this->m_world.createScene();

        /* ------------------------- Scene ChooseName --------------------------------*/

        this->m_world.createScene();

        /* ------------------------- Scene InGame --------------------------------*/
        this->m_world.createScene();
    }
}
