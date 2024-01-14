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

        while (!WindowShouldClose()) {
            if (this->m_network.isConnected()) {
                if (IsKeyDown(KEY_UP)) {
                    this->m_network.send(ecs::MessageType::PLAYER_MOVE, std::to_string(this->m_id) + ":up");
                } else if (IsKeyDown(KEY_DOWN)) {
                    this->m_network.send(ecs::MessageType::PLAYER_MOVE, std::to_string(this->m_id) + ":down");
                } else if (IsKeyDown(KEY_LEFT)) {
                    this->m_network.send(ecs::MessageType::PLAYER_MOVE, std::to_string(this->m_id) + ":left");
                } else if (IsKeyDown(KEY_RIGHT)) {
                    this->m_network.send(ecs::MessageType::PLAYER_MOVE, std::to_string(this->m_id) + ":right");
                } else if (IsKeyPressed(KEY_SPACE)) {
                    this->m_network.send(ecs::MessageType::PLAYER_SHOOT, std::to_string(this->m_id));
                }

                if (IsKeyReleased(KEY_UP) || IsKeyReleased(KEY_DOWN)) {
                    this->m_network.send(ecs::MessageType::PLAYER_MOVE, std::to_string(this->m_id) + ":stopy");
                } else if (IsKeyReleased(KEY_LEFT) || IsKeyReleased(KEY_RIGHT)) {
                    this->m_network.send(ecs::MessageType::PLAYER_MOVE, std::to_string(this->m_id) + ":stopx");
                }
            }

            BeginDrawing();
            ClearBackground(BLACK);

            this->m_world.update();

            EndDrawing();
        }

        CloseWindow();
        CloseAudioDevice();
        this->m_network.setRunning(false);
        this->m_network.send(ecs::MessageType::PLAYER_DISCONNECTED, std::to_string(this->m_id));
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

    void Game::setId(std::size_t id)
    {
        this->m_id = id;
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
