/*
** EPITECH PROJECT, 2024
** RType
** File description:
** LoadGame
*/

#include "Pong.hpp"

namespace game
{
    void Pong::LoadGame(ecs::Scene &scene)
    {
        /* Game Systems */
        this->world.registerSystems<
            ecs::MusicSystem,
            ecs::ControllableSystem,
            ecs::AnimationSystem,
            ecs::SpriteSystem,
            ecs::NameSystem,
            ecs::TextSystem,
            ecs::CollisionSystem,
            ecs::LifeSystem,
            ecs::ParallaxSystem,
            ecs::ModifierSystem,
            ecs::MovementSystem
        >(scene);

        /* Map background */
        ecs::Entity &Background = this->world.createEntity(scene);
        this->world.assign(Background, ecs::Position{65, 0});
        this->world.assign(Background, ecs::Sprite{"../assets/pong_map.png", ecs::Rectangle{0, 0, 1920, 1080}, ecs::Vector2{0, 0}});
        this->world.assign(Background, ecs::Scale{1, 1});
        this->world.assign(Background, ecs::Rotation{0});


        ecs::Entity &p1 = this->world.createEntity(scene);
        this->world.assign(p1, ecs::Position{10, 375});
        this->world.assign(p1, ecs::Sprite{"../assets/player1.png", ecs::Rectangle{0, 0, 50, 520}, ecs::Vector2{0, 0}});
        this->world.assign(p1, ecs::Scale{0.5, 0.5});
        this->world.assign(p1, ecs::Velocity{0, 0});
        this->world.assign(p1, ecs::Rotation{0});
        this->world.assign(p1, ecs::Acceleration{0, 0, 2});
        this->world.assign(p1, ecs::Collision({false, {}, false}));
        this->world.assign(p1, ecs::Controllable{
            std::unordered_map<int, std::tuple<ecs::ActionTrigger, std::function<void(ecs::SceneManager & sceneManager, ecs::Scene & scene, ecs::Entity * entity)>>> {
                {KEY_W, std::make_tuple<ecs::ActionTrigger, std::function<void(ecs::SceneManager&, ecs::Scene&, ecs::Entity*)>>(
                    ecs::ActionTrigger::Hold, [](ecs::SceneManager& sceneManager, ecs::Scene& scene, ecs::Entity*  entity) {
                        ecs::Position &actualPos = sceneManager.get<ecs::Position>(*entity);
                        if (actualPos.y > 0 && (actualPos.y - 25) > 0)
                            sceneManager.get<ecs::Position>(*entity).y -= 25;
                    }
                )},
                {KEY_S, std::make_tuple<ecs::ActionTrigger, std::function<void(ecs::SceneManager&, ecs::Scene&, ecs::Entity*)>>(
                    ecs::ActionTrigger::Hold, [](ecs::SceneManager& sceneManager, ecs::Scene& scene, ecs::Entity* entity) {
                        ecs::Position &actualPos = sceneManager.get<ecs::Position>(*entity);
                        if (actualPos.y < 1080 && (actualPos.y + 25) <= 820)
                            sceneManager.get<ecs::Position>(*entity).y += 25;
                    }
                )}
            }
        });

        ecs::Entity &p2 = this->world.createEntity(scene);
        this->world.assign(p2, ecs::Position{1885, 375});
        this->world.assign(p2, ecs::Sprite{"../assets/player2.png", ecs::Rectangle{0, 0, 50, 520}, ecs::Vector2{0, 0}});
        this->world.assign(p2, ecs::Scale{0.5, 0.5});
        this->world.assign(p2, ecs::Velocity{0, 0});
        this->world.assign(p2, ecs::Rotation{0});
        this->world.assign(p2, ecs::Acceleration{0, 0, 2});
        this->world.assign(p2, ecs::Collision({false, {}, false}));
        this->world.assign(p2, ecs::Controllable{
            std::unordered_map<int, std::tuple<ecs::ActionTrigger, std::function<void(ecs::SceneManager & sceneManager, ecs::Scene & scene, ecs::Entity * entity)>>> {
                {KEY_UP, std::make_tuple<ecs::ActionTrigger, std::function<void(ecs::SceneManager&, ecs::Scene&, ecs::Entity*)>>(
                    ecs::ActionTrigger::Hold, [](ecs::SceneManager& sceneManager, ecs::Scene& scene, ecs::Entity*  entity) {
                        ecs::Position &actualPos = sceneManager.get<ecs::Position>(*entity);
                        if (actualPos.y > 0 && (actualPos.y - 25) > 0)
                            sceneManager.get<ecs::Position>(*entity).y -= 25;
                    }
                )},
                {KEY_DOWN, std::make_tuple<ecs::ActionTrigger, std::function<void(ecs::SceneManager&, ecs::Scene&, ecs::Entity*)>>(
                    ecs::ActionTrigger::Hold, [](ecs::SceneManager& sceneManager, ecs::Scene& scene, ecs::Entity* entity) {
                        ecs::Position &actualPos = sceneManager.get<ecs::Position>(*entity);
                        if (actualPos.y < 1080 && (actualPos.y + 25) <= 820)
                            sceneManager.get<ecs::Position>(*entity).y += 25;
                    }
                )}
            }
        });

        ecs::Entity &ball = this->world.createEntity(scene);
        this->world.assign(ball, ecs::Position{850, 450});
        this->world.assign(ball, ecs::Sprite{"../assets/pong_ball.png", ecs::Rectangle{0, 0, 75, 75}, ecs::Vector2{0, 0}});
        this->world.assign(ball, ecs::Scale{1, 1});
        this->world.assign(ball, ecs::Rotation{0});
        this->world.assign(ball, ecs::Velocity({0,0}));
        this->world.assign(ball, ecs::Acceleration{0, 0, 8});
        this->world.assign(ball, ecs::Collision({false, {}, false}));
        this->world.assign(ball, ecs::Controllable{
            std::unordered_map<int, std::tuple<ecs::ActionTrigger, std::function<void(ecs::SceneManager & sceneManager, ecs::Scene & scene, ecs::Entity * entity)>>> {
                {KEY_SPACE, std::make_tuple<ecs::ActionTrigger, std::function<void(ecs::SceneManager&, ecs::Scene&, ecs::Entity*)>>(
                    ecs::ActionTrigger::Press, [](ecs::SceneManager& sceneManager, ecs::Scene& scene, ecs::Entity*  entity) {
                        sceneManager.get<ecs::Velocity>(*entity).dx = 5;
                    }
                )}
            }
        });
    }
}
