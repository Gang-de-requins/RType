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
        this->m_world.loadTextures({ "assets/characters.gif", "assets/28.png" });

        while (!WindowShouldClose()) {
            if (this->m_network.isConnected()) {
                if (IsKeyPressed(KEY_UP)) {
                    ecs::Move msg = {ecs::MessageType::GoTop};
                    this->m_network.send(msg, ecs::MessageType::Move);
                }
                if (IsKeyPressed(KEY_DOWN)) {
                    ecs::Move msg = {ecs::MessageType::GoBottom};
                    this->m_network.send(msg, ecs::MessageType::Move);
                } if (IsKeyPressed(KEY_LEFT)) {
                    ecs::Move msg = {ecs::MessageType::GoLeft};
                    this->m_network.send(msg, ecs::MessageType::Move);
                } if (IsKeyPressed(KEY_RIGHT)) {
                    ecs::Move msg = {ecs::MessageType::GoRight};
                    this->m_network.send(msg, ecs::MessageType::Move);
                }
                if (IsKeyPressed(KEY_SPACE)) {
                    ecs::Move msg = {ecs::MessageType::GoRight};
                    this->m_network.send(msg, ecs::MessageType::NewMissile);
                }

                if (IsKeyReleased(KEY_UP) || IsKeyReleased(KEY_DOWN)) {
                    ecs::Move msg = {ecs::MessageType::StopY};
                    this->m_network.send(msg, ecs::MessageType::Move);
                } else if (IsKeyReleased(KEY_LEFT) || IsKeyReleased(KEY_RIGHT)) {
                    ecs::Move msg = {ecs::MessageType::StopX};
                    this->m_network.send(msg, ecs::MessageType::Move);
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
        // this->m_network.send(ecs::MessageType::PLAYER_DISCONNECTED, std::to_string(this->m_id));
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

    std::string Game::getPlayerName() const
    {
        return this->m_playerName;
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

        /* ------------------------- Scene Win --------------------------------*/
        this->m_world.createScene();

        /* ------------------------- Scene GameOver --------------------------------*/
        this->m_world.createScene();
    }
}
