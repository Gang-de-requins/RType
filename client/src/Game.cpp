#include "Game.hpp"

namespace rtype {
    Game::Game(const std::string &ip, const unsigned short port, const std::string &playerName) :
    c_playerName(playerName)
    {
        initScenes();
        this->m_network.connect(ip, port, *this, this->c_playerName);
    }

    Game::~Game()
    {
    }

    void Game::run()
    {
        InitAudioDevice();
        InitWindow(1920, 1080, "rtype");
        SetTargetFPS(60);
        this->m_world.loadTextures({ "assets/characters.gif" });

        while (!WindowShouldClose())
        {
            if (IsKeyPressed(KEY_UP))
                this->m_network.send(::Network::MessageType::GoTop, this->c_playerName);
            if (IsKeyPressed(KEY_DOWN))
                this->m_network.send(::Network::MessageType::GoBottom, this->c_playerName);
            if (IsKeyPressed(KEY_LEFT))
                this->m_network.send(::Network::MessageType::GoLeft, this->c_playerName);
            if (IsKeyPressed(KEY_RIGHT))
                this->m_network.send(::Network::MessageType::GoRight, this->c_playerName);
            if (IsKeyReleased(KEY_UP))
                this->m_network.send(::Network::MessageType::StopTop, this->c_playerName);
            if (IsKeyReleased(KEY_DOWN))
                this->m_network.send(::Network::MessageType::StopBottom, this->c_playerName);
            if (IsKeyReleased(KEY_LEFT))
                this->m_network.send(::Network::MessageType::StopLeft, this->c_playerName);
            if (IsKeyReleased(KEY_RIGHT))
                this->m_network.send(::Network::MessageType::StopRight, this->c_playerName);

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
            ecs::LifeSystem,
            ecs::ParallaxSystem
        >(inGame);

        ecs::Entity &ParallaxBack1 = this->m_world.createEntity(inGame);
        this->m_world.assign(ParallaxBack1, ecs::Position{0, 0});
        this->m_world.assign(ParallaxBack1, ecs::Velocity{-3, 0});
        this->m_world.assign(ParallaxBack1, ecs::Sprite{"assets/space-back.png", ecs::Rectangle{0, 0, 7596, 1080}, ecs::Vector2{0, 0}});
        this->m_world.assign(ParallaxBack1, ecs::Parallax{true});
        this->m_world.assign(ParallaxBack1, ecs::Acceleration{0, 0, 3});
        this->m_world.assign(ParallaxBack1, ecs::Scale{1, 1});
        this->m_world.assign(ParallaxBack1, ecs::Rotation{0});

        ecs::Entity &ParallaxBack2 = this->m_world.createEntity(inGame);
        this->m_world.assign(ParallaxBack2, ecs::Position{1920, 0});
        this->m_world.assign(ParallaxBack2, ecs::Velocity{-1.5, 0});
        this->m_world.assign(ParallaxBack2, ecs::Sprite{"assets/far-planets.png", ecs::Rectangle{0, 0, 272, 160}, ecs::Vector2{0, 0}});
        this->m_world.assign(ParallaxBack2, ecs::Parallax{true});
        this->m_world.assign(ParallaxBack2, ecs::Acceleration{0, 0, 2});
        this->m_world.assign(ParallaxBack2, ecs::Scale{1920 / 272, 1080 / 160});
        this->m_world.assign(ParallaxBack2, ecs::Rotation{0});

        ecs::Entity &myPlayer = this->m_world.createEntity(inGame);
        this->m_world.assign(myPlayer, ecs::Position{200, 200});
        this->m_world.assign(myPlayer, ecs::Health{100});
        this->m_world.assign(myPlayer, ecs::Velocity{0, 0});
        this->m_world.assign(myPlayer, ecs::Sprite{"assets/characters2.gif", ecs::Rectangle{0, 0, 32, 32}, ecs::Vector2{0, 0}});
        this->m_world.assign(myPlayer, ecs::Acceleration{0, 0, 4});
        this->m_world.assign(myPlayer, ecs::Scale{2, 2});
        this->m_world.assign(myPlayer, ecs::Rotation{0});
        this->m_world.assign(myPlayer, ecs::Controllable{KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE, 0.05, std::chrono::steady_clock::now()});
        this->m_world.assign(myPlayer, ecs::Collision{false, {}, false});
        this->m_world.assign(myPlayer, ecs::Animation{ecs::Rectangle{0, 0, 32, 0}, 8, 0, 150, std::chrono::steady_clock::now()});
        this->m_world.assign(myPlayer, ecs::Name{this->c_playerName, ecs::Position{-20, -20}});

        this->m_players.push_back(Player(myPlayer, this->c_playerName));

        ecs::Entity &SoundPlayer = this->m_world.createEntity(inGame);
        this->m_world.assign(SoundPlayer, ecs::Sound{"assets/weird.wav"});
    }
}
