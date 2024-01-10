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
            // if (IsKeyPressed(KEY_UP))
            //     this->m_network.send(::Network::MessageType::GoTop, this->m_playerName);
            // if (IsKeyPressed(KEY_DOWN))
            //     this->m_network.send(::Network::MessageType::GoBottom, this->m_playerName);
            // if (IsKeyPressed(KEY_LEFT))
            //     this->m_network.send(::Network::MessageType::GoLeft, this->m_playerName);
            // if (IsKeyPressed(KEY_RIGHT))
            //     this->m_network.send(::Network::MessageType::GoRight, this->m_playerName);
            // if (IsKeyReleased(KEY_UP))
            //     this->m_network.send(::Network::MessageType::StopTop, this->m_playerName);
            // if (IsKeyReleased(KEY_DOWN))
            //     this->m_network.send(::Network::MessageType::StopBottom, this->m_playerName);
            // if (IsKeyReleased(KEY_LEFT))
            //     this->m_network.send(::Network::MessageType::StopLeft, this->m_playerName);
            // if (IsKeyReleased(KEY_RIGHT))
            //     this->m_network.send(::Network::MessageType::StopRight, this->m_playerName);
            if (IsKeyPressed(KEY_SPACE)) {
                ecs::SceneManager &sceneManager = this->m_world.getSceneManager();
                auto entities = sceneManager.view<ecs::Controllable>(sceneManager.getCurrentScene());

                for (auto &entity : entities) {
                    ecs::Controllable &controllable = sceneManager.get<ecs::Controllable>(*entity);
                    if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - controllable.shootUpdate).count() >= controllable.timeOut) {
                        this->m_network.send(::Network::MessageType::NewMissile, this->m_playerName);
                    }
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
    }

    ecs::World &Game::getWorld()
    {
        return this->m_world;
    }

    float Game::getOffsetColorSpaceship() const
    {
        return this->m_players.size() * 16;
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

        ecs::Scene &inMenuSettings = this->m_world.createScene();

        /* ------------------------- Scene ChooseName --------------------------------*/

        ecs::Scene &chooseName = this->m_world.createScene();

        /* ------------------------- Scene InGame --------------------------------*/
        ecs::Scene &inGame = this->m_world.createScene();

    }
}
