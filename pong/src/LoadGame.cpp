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
            // ecs::ControllableSystem,
            ecs::AnimationSystem,
            ecs::SpriteSystem,
            ecs::NameSystem,
            ecs::TextSystem,
            ecs::CollisionSystem,
            ecs::LifeSystem,
            ecs::ParallaxSystem,
            ecs::ModifierSystem
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
        this->world.assign(p1, ecs::Rotation{0});
        // this->world.assign(p1, ecs::Controllable{KEY_Z, KEY_S});
        this->world.assign(p1, ecs::Acceleration{0, 0, 8});

        ecs::Entity &p2 = this->world.createEntity(scene);
        this->world.assign(p2, ecs::Position{1885, 375});
        this->world.assign(p2, ecs::Sprite{"../assets/player2.png", ecs::Rectangle{0, 0, 50, 520}, ecs::Vector2{0, 0}});
        this->world.assign(p2, ecs::Scale{0.5, 0.5});
        this->world.assign(p2, ecs::Rotation{0});
        // this->world.assign(p2, ecs::Controllable{KEY_UP, KEY_DOWN});
        this->world.assign(p2, ecs::Acceleration{0, 0, 8});


        ecs::Entity &ball = this->world.createEntity(scene);
        this->world.assign(ball, ecs::Position{850, 450});
        this->world.assign(ball, ecs::Sprite{"../assets/pong_ball.png", ecs::Rectangle{0, 0, 75, 75}, ecs::Vector2{0, 0}});
        this->world.assign(ball, ecs::Scale{1, 1});
        this->world.assign(ball, ecs::Rotation{0});
        this->world.assign(ball, ecs::Acceleration{0, 0, 8});
    }
}