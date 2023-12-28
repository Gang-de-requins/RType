#include "Game.hpp"

namespace rtype {
    Game::Game(const std::string &ip, const unsigned short port, const std::string &playerName) :
    m_playerName(playerName)
    {
        initScenes();
        this->m_network.connect(ip, port, *this, this->m_playerName);
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

         this->m_world.registerSystems<
            ecs::MusicSystem,
            ecs::ControllableSystem,
            ecs::MovementSystem,
            ecs::CollisionSystem,
            ecs::LifeSystem,
            ecs::ParallaxSystem,
            ecs::RenderSystem,
            ecs::ClickableSystem
        >(inMenu);


        ecs::Entity &ButtonPlay = this->m_world.createEntity(inMenu);
        this->m_world.assign(ButtonPlay, ecs::Position{500, 500});
        this->m_world.assign(ButtonPlay, ecs::Sprite{"assets/buttonPlay.png", ecs::Rectangle{0, 0, 300, 153}, ecs::Vector2{0, 0}});
        this->m_world.assign(ButtonPlay, ecs::Scale{1, 1});
        this->m_world.assign(ButtonPlay, ecs::Rotation{0});
        this->m_world.assign(ButtonPlay, ecs::Clickable{false, [this](ecs::Clickable&) {
            std::cout << "ButtonPlay clicked" << std::endl;
            this->m_world.switchToScene(1);
        }});

        ecs::Entity &PlayerTextInput = this->m_world.createEntity(inMenu);
        this->m_world.assign(PlayerTextInput, ecs::Position{500, 300});
        this->m_world.assign(PlayerTextInput, ecs::Rectangle{0, 0, 300, 100});
        this->m_world.assign(PlayerTextInput, ecs::TextInput{10, ecs::Position{500, 325}});
        this->m_world.assign(PlayerTextInput, ecs::Scale{1, 1});
        this->m_world.assign(PlayerTextInput, ecs::Rotation{0});
        this->m_world.assign(PlayerTextInput, ecs::Clickable{false, [this](ecs::Clickable&) {
            std::cout << "PlayerTextInput clicked" << std::endl;
            ecs::Entity &PlayerTextInput = this->m_world.getEntityById(this->m_world.getCurrentScene(), 1);
            ecs::TextInput &textInput = this->m_world.get<ecs::TextInput>(PlayerTextInput);

            this->m_playerName = textInput.content;
            textInput.isFocused = true;
        }});
        this->m_world.assign(PlayerTextInput, ecs::Color{200, 200, 200, 255});
        this->m_world.assign(PlayerTextInput, ecs::FontSize{50});
        this->m_world.assign(PlayerTextInput, ecs::TextColor{0, 0, 0, 255});

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
        this->m_world.assign(myPlayer, ecs::Name{this->m_playerName, ecs::Position{-20, -20}});

        this->m_players.push_back(Player(myPlayer, this->m_playerName));

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
