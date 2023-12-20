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
            if (IsKeyPressed(KEY_UP))
                this->m_network.send(ecs::MessageType::GoTop, "Player1");
            if (IsKeyPressed(KEY_DOWN))
                this->m_network.send(ecs::MessageType::GoBottom, "Player1");
            if (IsKeyPressed(KEY_LEFT))
                this->m_network.send(ecs::MessageType::GoLeft, "Player1");
            if (IsKeyPressed(KEY_RIGHT))
                this->m_network.send(ecs::MessageType::GoRight, "Player1");
            
            if (IsKeyReleased(KEY_UP))
                this->m_network.send(ecs::MessageType::StopTop, "Player1");
            if (IsKeyReleased(KEY_DOWN))
                this->m_network.send(ecs::MessageType::StopBottom, "Player1");
            if (IsKeyReleased(KEY_LEFT))
                this->m_network.send(ecs::MessageType::StopLeft, "Player1");
            if (IsKeyReleased(KEY_RIGHT))
                this->m_network.send(ecs::MessageType::StopRight, "Player1");

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
        ecs::Scene &inGame = this->m_world.createScene();

        this->m_world.registerSystems<
            ecs::MusicSystem,
            ecs::ControllableSystem,
            ecs::AnimationSystem,
            ecs::MovementSystem,
            ecs::SpriteSystem,
            ecs::NameSystem,
            ecs::TextSystem,
            ecs::CollisionSystem,
            ecs::LifeSystem
        >(inGame);
        ecs::Entity &myPlayer = this->m_world.createEntity(inGame);

        this->m_world.assign(myPlayer, ecs::Position{200, 200});
        this->m_world.assign(myPlayer, ecs::Health{100});
        this->m_world.assign(myPlayer, ecs::Velocity{0, 0});
        this->m_world.assign(myPlayer, ecs::Sprite{"assets/characters.gif", ecs::Rectangle{0, 0, 32, 16}, ecs::Vector2{0, 0}});
        this->m_world.assign(myPlayer, ecs::Acceleration{0, 0, 4});
        this->m_world.assign(myPlayer, ecs::Scale{1, 1});
        this->m_world.assign(myPlayer, ecs::Rotation{0});
        this->m_world.assign(myPlayer, ecs::Controllable{KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT});
        this->m_world.assign(myPlayer, ecs::Collision{false, {}});
        this->m_world.assign(myPlayer, ecs::Animation{ecs::Rectangle{0, 0, 32, 0}, 4, 0, 300, std::chrono::steady_clock::now()});
        this->m_world.assign(myPlayer, ecs::Name{"Player 1", ecs::Position{-20, -20}});

        this->m_players.push_back(Player(myPlayer, "Player 1"));

        ecs::Entity &myPlayer2 = this->m_world.createEntity(inGame);
        this->m_world.assign(myPlayer2, ecs::Position{300, 300});
        this->m_world.assign(myPlayer2, ecs::Health{100});
        this->m_world.assign(myPlayer2, ecs::Velocity{0, 0});
        this->m_world.assign(myPlayer2, ecs::Sprite{"assets/characters.gif", ecs::Rectangle{0, 0, 32, 16}, ecs::Vector2{0, 0}});
        this->m_world.assign(myPlayer2, ecs::Acceleration{0, 0, 4});
        this->m_world.assign(myPlayer2, ecs::Scale{1, 1});
        this->m_world.assign(myPlayer2, ecs::Rotation{0});
        this->m_world.assign(myPlayer2, ecs::Controllable{KEY_W, KEY_S, KEY_A, KEY_D});
        this->m_world.assign(myPlayer2, ecs::Collision{false, {}});
        this->m_world.assign(myPlayer2, ecs::Animation{ecs::Rectangle{0, 0, 32, 0}, 4, 0, 300, std::chrono::steady_clock::now()});
        this->m_world.assign(myPlayer2, ecs::Damage{10});
    }
}
