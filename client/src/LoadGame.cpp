#include "Game.hpp"

namespace rtype {
    void Game::loadGame(ecs::Scene &scene)
    {
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
        >(scene);

        std::cout << "In Game" << std::endl;

        ecs::Entity &ParallaxBack1 = this->m_world.createEntity(scene);
        this->m_world.assign(ParallaxBack1, ecs::Position{0, 0});
        this->m_world.assign(ParallaxBack1, ecs::Velocity{-3, 0});
        this->m_world.assign(ParallaxBack1, ecs::Sprite{"assets/space-back.png", ecs::Rectangle{0, 0, 7596, 1080}, ecs::Vector2{0, 0}});
        this->m_world.assign(ParallaxBack1, ecs::Parallax{true});
        this->m_world.assign(ParallaxBack1, ecs::Acceleration{0, 0, 3});
        this->m_world.assign(ParallaxBack1, ecs::Scale{1, 1});
        this->m_world.assign(ParallaxBack1, ecs::Rotation{0});

        ecs::Entity &ParallaxBack2 = this->m_world.createEntity(scene);
        this->m_world.assign(ParallaxBack2, ecs::Position{1920, 0});
        this->m_world.assign(ParallaxBack2, ecs::Velocity{-1.5, 0});
        this->m_world.assign(ParallaxBack2, ecs::Sprite{"assets/far-planets.png", ecs::Rectangle{0, 0, 272, 160}, ecs::Vector2{0, 0}});
        this->m_world.assign(ParallaxBack2, ecs::Parallax{true});
        this->m_world.assign(ParallaxBack2, ecs::Acceleration{0, 0, 2});
        this->m_world.assign(ParallaxBack2, ecs::Scale{1920 / 272, 1080 / 160});
        this->m_world.assign(ParallaxBack2, ecs::Rotation{0});

        std::cout << "PlayerTextInput " << this->m_playerName << std::endl;

        ecs::Entity &myPlayer = this->m_world.createEntity(scene);
        this->m_world.assign(myPlayer, ecs::Position{200, 200});
        this->m_world.assign(myPlayer, ecs::Health{100});
        this->m_world.assign(myPlayer, ecs::Velocity{0, 0});
        this->m_world.assign(myPlayer, ecs::Sprite{"assets/characters2.gif", ecs::Rectangle{0, 0, 32, 32}, ecs::Vector2{0, 0}});
        this->m_world.assign(myPlayer, ecs::Acceleration{0, 0, 4});
        this->m_world.assign(myPlayer, ecs::Scale{2, 2});
        this->m_world.assign(myPlayer, ecs::Rotation{0});
        this->m_world.assign(myPlayer, ecs::Controllable{
            std::unordered_map<int, std::tuple<ecs::ActionTrigger, std::function<void(ecs::SceneManager & sceneManager, ecs::Scene & scene, ecs::Entity * entity)>>> {
                {KEY_UP, std::make_tuple<ecs::ActionTrigger, std::function<void(ecs::SceneManager&, ecs::Scene&, ecs::Entity*)>>(
                    ecs::ActionTrigger::Hold, [](ecs::SceneManager& sceneManager, ecs::Scene& scene, ecs::Entity* entity) {
                        static_cast<void>(sceneManager);

                        scene.events[ecs::EventType::Input].push_back({
                            ecs::GameEvent::MoveUp,
                            {entity}
                        });
                    }
                )},
                {KEY_DOWN, std::make_tuple<ecs::ActionTrigger, std::function<void(ecs::SceneManager&, ecs::Scene&, ecs::Entity*)>>(
                    ecs::ActionTrigger::Hold, [](ecs::SceneManager& sceneManager, ecs::Scene& scene, ecs::Entity* entity) {
                        static_cast<void>(sceneManager);

                        scene.events[ecs::EventType::Input].push_back({
                            ecs::GameEvent::MoveDown,
                            {entity}
                        });
                    }
                )},
                {KEY_LEFT, std::make_tuple<ecs::ActionTrigger, std::function<void(ecs::SceneManager&, ecs::Scene&, ecs::Entity*)>>(
                    ecs::ActionTrigger::Hold, [](ecs::SceneManager& sceneManager, ecs::Scene& scene, ecs::Entity* entity) {
                        static_cast<void>(sceneManager);

                        scene.events[ecs::EventType::Input].push_back({
                            ecs::GameEvent::MoveLeft,
                            {entity}
                        });
                    }
                )},
                {KEY_RIGHT, std::make_tuple<ecs::ActionTrigger, std::function<void(ecs::SceneManager&, ecs::Scene&, ecs::Entity*)>>(
                    ecs::ActionTrigger::Hold, [](ecs::SceneManager& sceneManager, ecs::Scene& scene, ecs::Entity* entity) {
                        static_cast<void>(sceneManager);

                        scene.events[ecs::EventType::Input].push_back({
                            ecs::GameEvent::MoveRight,
                            {entity}
                        });
                    }
                )},
                {KEY_SPACE, std::make_tuple<ecs::ActionTrigger, std::function<void(ecs::SceneManager&, ecs::Scene&, ecs::Entity*)>>(
                    ecs::ActionTrigger::Press, [](ecs::SceneManager& sceneManager, ecs::Scene& scene, ecs::Entity* entity) {
                        if (sceneManager.has<ecs::Shooter>(*entity)) {
                            ecs::Shooter& shooter = sceneManager.get<ecs::Shooter>(*entity);

                            if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - shooter.lastShotTime) >= shooter.cooldown) {
                                shooter.lastShotTime = std::chrono::steady_clock::now();
                                scene.events[ecs::EventType::Spawn].push_back({
                                    ecs::GameEvent::SpawnPlayerBullet,
                                    {entity}
                                });
                            }
                        }
                    }
                )},
            }
        });
        this->m_world.assign(myPlayer, ecs::Collision{false, {}, false});
        this->m_world.assign(myPlayer, ecs::Animation{ecs::Rectangle{0, 0, 32, 0}, 8, 0, 150, std::chrono::steady_clock::now()});
        this->m_world.assign(myPlayer, ecs::Name{this->m_playerName, ecs::Position{-20, -20}});
        this->m_world.assign(myPlayer, ecs::Shooter{std::chrono::milliseconds(500), std::chrono::steady_clock::now()});

        this->m_players.push_back(Player(myPlayer, this->m_playerName));

        ecs::Entity &SoundPlayer = this->m_world.createEntity(scene);
        this->m_world.assign(SoundPlayer, ecs::Sound{"assets/weird.wav"});

        ecs::Entity &music = this->m_world.createEntity(scene);
        this->m_world.assign(music, ecs::Music{"assets/mini1111.xm", 1.0f, true});

        ecs::Entity &boost = this->m_world.createEntity(scene);
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
