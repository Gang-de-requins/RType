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
            // if (IsKeyPressed(KEY_UP))
            //     this->m_network.send(::Network::MessageType::GoTop, this->c_playerName);
            // if (IsKeyPressed(KEY_DOWN))
            //     this->m_network.send(::Network::MessageType::GoBottom, this->c_playerName);
            // if (IsKeyPressed(KEY_LEFT))
            //     this->m_network.send(::Network::MessageType::GoLeft, this->c_playerName);
            // if (IsKeyPressed(KEY_RIGHT))
            //     this->m_network.send(::Network::MessageType::GoRight, this->c_playerName);
            // if (IsKeyReleased(KEY_UP))
            //     this->m_network.send(::Network::MessageType::StopTop, this->c_playerName);
            // if (IsKeyReleased(KEY_DOWN))
            //     this->m_network.send(::Network::MessageType::StopBottom, this->c_playerName);
            // if (IsKeyReleased(KEY_LEFT))
            //     this->m_network.send(::Network::MessageType::StopLeft, this->c_playerName);
            // if (IsKeyReleased(KEY_RIGHT))
            //     this->m_network.send(::Network::MessageType::StopRight, this->c_playerName);
            if (IsKeyPressed(KEY_SPACE)) {
                ecs::SceneManager &sceneManager = this->m_world.getSceneManager();
                auto entities = sceneManager.view<ecs::Controllable>(sceneManager.getCurrentScene());
            
                for (auto &entity : entities) {
                    ecs::Controllable &controllable = sceneManager.get<ecs::Controllable>(*entity);
                    if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - controllable.shootUpdate).count() >= controllable.timeOut) {
                        this->m_network.send(::Network::MessageType::NewMissile, this->c_playerName);
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
            ecs::ParallaxSystem,
            ecs::ClickableSystem
        >(inMenu);


        ecs::Entity &Bakckground = this->m_world.createEntity(inMenu);
        this->m_world.assign(Bakckground, ecs::Position{0, 0});
        this->m_world.assign(Bakckground, ecs::Sprite{"assets/Menu/Space-Back-Menu.png", ecs::Rectangle{0, 0, 1920, 1080}, ecs::Vector2{0, 0}});
        this->m_world.assign(Bakckground, ecs::Scale{1, 1});
        this->m_world.assign(Bakckground, ecs::Rotation{0});

        ecs::Entity &Title = this->m_world.createEntity(inMenu);
        this->m_world.assign(Title, ecs::Position{350, 5});
        this->m_world.assign(Title, ecs::Sprite{"assets/Menu/r-type.png", ecs::Rectangle{0, 0, 1258, 481}, ecs::Vector2{0, 0}});
        this->m_world.assign(Title, ecs::Scale{1, 1});
        this->m_world.assign(Title, ecs::Rotation{0});


        ecs::Entity &ButtonSettings = this->m_world.createEntity(inMenu);
        this->m_world.assign(ButtonSettings, ecs::Position{810, 460});
        this->m_world.assign(ButtonSettings, ecs::Sprite{"assets/Menu/buttonSettings.png", ecs::Rectangle{0, 0, 300, 153}, ecs::Vector2{0, 0}});
        this->m_world.assign(ButtonSettings, ecs::Scale{1, 1});
        this->m_world.assign(ButtonSettings, ecs::Rotation{0});
        this->m_world.assign(ButtonSettings, ecs::Clickable{false, [this](ecs::Clickable&) {this->m_world.switchToScene(1);}});

        // ecs::Entity &ButtonPlay = this->m_world.createEntity(inMenu);
        // this->m_world.assign(ButtonPlay, ecs::Position{810, 300});
        // this->m_world.assign(ButtonPlay, ecs::Sprite{"assets/Menu/buttonPlay.png", ecs::Rectangle{0, 0, 300, 153}, ecs::Vector2{0, 0}});
        // this->m_world.assign(ButtonPlay, ecs::Scale{1, 1});
        // this->m_world.assign(ButtonPlay, ecs::Rotation{0});
        // this->m_world.assign(ButtonPlay, ecs::Clickable{false, [this](ecs::Clickable&) {this->m_world.switchToScene(2);}});

        /* ------------------------- Scene InSettings--------------------------------*/

        ecs::Scene &inMenuSettings = this->m_world.createScene();

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
            ecs::ParallaxSystem,
            ecs::ClickableSystem
        >(inMenuSettings);

        ecs::Entity &Bakckground_Settings = this->m_world.createEntity(inMenuSettings);
        this->m_world.assign(Bakckground_Settings, ecs::Position{0, 0});
        this->m_world.assign(Bakckground_Settings, ecs::Sprite{"assets/Settings/Space-Back-Settings.png", ecs::Rectangle{0, 0, 1920, 1080}, ecs::Vector2{0, 0}});
        this->m_world.assign(Bakckground_Settings, ecs::Scale{1, 1});
        this->m_world.assign(Bakckground_Settings, ecs::Rotation{0});

        ecs::Entity &ButtonMusic = this->m_world.createEntity(inMenuSettings);
        this->m_world.assign(ButtonMusic, ecs::Position{550, 90});
        this->m_world.assign(ButtonMusic, ecs::Sprite{"assets/Settings/buttonMusic.png", ecs::Rectangle{0, 0, 210, 210}, ecs::Vector2{0, 0}});
        this->m_world.assign(ButtonMusic, ecs::Scale{0.6, 0.6});
        this->m_world.assign(ButtonMusic, ecs::Rotation{0});
        this->m_world.assign(ButtonMusic, ecs::Clickable{false, [this](ecs::Clickable&) {this->m_world.switchToScene(1);}});

        ecs::Entity &ButtonPause = this->m_world.createEntity(inMenuSettings);
        this->m_world.assign(ButtonPause, ecs::Position{530, 230});
        this->m_world.assign(ButtonPause, ecs::Sprite{"assets/Settings/buttonPause.png", ecs::Rectangle{0, 0, 210, 210}, ecs::Vector2{0, 0}});
        this->m_world.assign(ButtonPause, ecs::Scale{0.3, 0.3});
        this->m_world.assign(ButtonPause, ecs::Rotation{0});

        ecs::Entity &ButtonPlay = this->m_world.createEntity(inMenuSettings);
        this->m_world.assign(ButtonPlay, ecs::Position{630, 230});
        this->m_world.assign(ButtonPlay, ecs::Sprite{"assets/Settings/buttonPlay.png", ecs::Rectangle{0, 0, 210, 210}, ecs::Vector2{0, 0}});
        this->m_world.assign(ButtonPlay, ecs::Scale{0.3, 0.3});
        this->m_world.assign(ButtonPlay, ecs::Rotation{0});

        ecs::Entity &ButtonBackward = this->m_world.createEntity(inMenuSettings);
        this->m_world.assign(ButtonBackward, ecs::Position{5, 995});
        this->m_world.assign(ButtonBackward, ecs::Sprite{"assets/Settings/buttonBackward.png", ecs::Rectangle{0, 0, 210, 210}, ecs::Vector2{0, 0}});
        this->m_world.assign(ButtonBackward, ecs::Scale{0.4, 0.4});
        this->m_world.assign(ButtonBackward, ecs::Rotation{0});


        /* ------------------------- Scene InGame --------------------------------*/
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
            ecs::ParallaxSystem,
            ecs::ModifierSystem
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

        ecs::Entity &music = this->m_world.createEntity(inGame);
        this->m_world.assign(music, ecs::Music{"assets/mini1111.xm"});

        ecs::Entity &boost = this->m_world.createEntity(inGame);
        this->m_world.assign(boost, ecs::Position{500, 200});
        this->m_world.assign(boost, ecs::Collision{false, {}, true});
        this->m_world.assign(boost, ecs::Sprite{"assets/characters.gif", ecs::Rectangle{0, 0, 32, 16}, ecs::Vector2{0, 0}});
        this->m_world.assign(boost, ecs::Scale{1, 1});
        this->m_world.assign(boost, ecs::Rotation{0});
        this->m_world.assign(boost, ecs::Modifier{{
            {std::type_index(typeid(ecs::Scale)), ecs::Scale{-1, -1}},
        }, true});
    }
}
