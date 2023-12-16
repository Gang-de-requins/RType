#include "Game.hpp"

namespace rtype {
    Game::Game()
    {
        initScenes();
        this->m_network.connect("127.0.0.1", 12345, *this);
    }

    Game::~Game()
    {
    }

    void Game::run()
    {
        InitAudioDevice();
        InitWindow(800, 450, "rtype");
        SetTargetFPS(60);
        this->m_world.loadTextures({ "assets/characters.gif" });

        while (!WindowShouldClose())
        {
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
        // return this->m_players.size() * 16;
        float offset = this->m_players.size() * 16;
        std::cout << "Offset: " << offset << std::endl;
        return offset;
    }

    void Game::addPlayer(Player &player)
    {
        this->m_players.push_back(player);
    }

    /* ---------------------------- PRIVATE FUNCTIONS --------------------------- */

    void Game::initScenes()
    {
        ecs::Scene &inGame = this->m_world.createScene();

        this->m_world.registerSystems<ecs::MusicSystem, ecs::ControllableSystem, ecs::AnimationSystem, ecs::MovementSystem, ecs::SpriteSystem, ecs::TextSystem>(inGame);
        ecs::Entity &myPlayer = this->m_world.createEntity(inGame);

        this->m_world.assign(myPlayer, ecs::Position{200, 200});
        this->m_world.assign(myPlayer, ecs::Position{200, 200});
        this->m_world.assign(myPlayer, ecs::Velocity{0, 0});
        this->m_world.assign(myPlayer, ecs::Sprite{"assets/characters.gif", ecs::Rectangle{0, 0, 32, 16}, ecs::Vector2{0, 0}});
        this->m_world.assign(myPlayer, ecs::Acceleration{0, 0, 4});
        this->m_world.assign(myPlayer, ecs::Scale{1, 1});
        this->m_world.assign(myPlayer, ecs::Rotation{0});
        this->m_world.assign(myPlayer, ecs::Controllable{KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT});

        ecs::Entity &myPlayerText = this->m_world.createEntity(inGame);
        this->m_world.assign(myPlayerText, ecs::Position{180, 180});
        this->m_world.assign(myPlayerText, ecs::Text{"Player 1"});
        this->m_world.assign(myPlayerText, ecs::FontSize{20});
        this->m_world.assign(myPlayerText, ecs::Color{ 255, 255, 255, 255 });
        this->m_world.assign(myPlayerText, ecs::Controllable{KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT});
        this->m_world.assign(myPlayerText, ecs::Velocity{0, 0});
        this->m_world.assign(myPlayerText, ecs::Acceleration{0, 0, 4});

        this->m_players.push_back(Player(myPlayer, myPlayerText, "Player 1"));
    }
}
