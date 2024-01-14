#include "EntityTemplate.hpp"

namespace server {
    EntityTemplate::EntityTemplate()
    {
    }

    EntityTemplate::~EntityTemplate()
    {
    }

    void EntityTemplate::player(ecs::World &world, const std::string &tag, int x, int y)
    {
        static_cast<void>(tag);
        ecs::Entity &entity = world.createEntity(world.getCurrentScene());

        std::cout << "Id: " << entity.id << std::endl;
        world.assign(entity, ecs::Position{static_cast<float>(x), static_cast<float>(y)});
        world.assign(entity, ecs::Velocity{0, 0});
        world.assign(entity, ecs::Health{100});
        world.assign(entity, ecs::Sprite{"assets/characters2.gif", ecs::Rectangle{0, 0, 32, 32}, ecs::Vector2{0, 0}});
        world.assign(entity, ecs::Acceleration{0, 0, 4});
        world.assign(entity, ecs::Scale{2, 2});
        world.assign(entity, ecs::Rotation{0});
        world.assign(entity, ecs::Collision{false, {}, true });
        world.assign(entity, ecs::Shooter{std::chrono::milliseconds(500), std::chrono::steady_clock::now()});
    }

    void EntityTemplate::playerBullet(ecs::World &world, const std::string &tag, int x, int y)
    {
        static_cast<void>(tag);
        ecs::Entity &entity = world.createEntity(world.getCurrentScene());

        world.assign(entity, ecs::Position{static_cast<float>(x), static_cast<float>(y)});
        world.assign(entity, ecs::Sprite{ "assets/28.png", ecs::Rectangle{0, 0, 210, 92}, ecs::Vector2{0, 0} });
        world.assign(entity, ecs::Acceleration{ 1, 0, 15 });
        world.assign(entity, ecs::Scale{ 0.25, 0.25 });
        world.assign(entity, ecs::Rotation{ 0 });
        world.assign(entity, ecs::Collision{ false, {}, true });
        world.assign(entity, ecs::Sound{ "assets/weird.wav" });
        world.assign(entity, ecs::Damage{ 10 });
    }

    void EntityTemplate::enemy(ecs::World &world, int x, int y)
    {
        ecs::Entity &entity = world.createEntity(world.getCurrentScene());

        world.assign(entity, ecs::Position{static_cast<float>(x), static_cast<float>(y)});
        world.assign(entity, ecs::Velocity{-2, 0});
        world.assign(entity, ecs::Health{100});
        world.assign(entity, ecs::Sprite{"assets/characters.gif", ecs::Rectangle{0, 0, 32, 32}, ecs::Vector2{0, 0}});
        world.assign(entity, ecs::Acceleration{0, 0, 4});
        world.assign(entity, ecs::Scale{2, 2});
        world.assign(entity, ecs::Rotation{0});
        world.assign(entity, ecs::Collision{ false, {}, true });
    }

    void EntityTemplate::enemyBullet(ecs::World &world, const std::string &tag, int x, int y)
    {
        static_cast<void>(tag);
        ecs::Entity entity = world.createEntity(world.getCurrentScene());

        world.assign(entity, ecs::Position{static_cast<float>(x), static_cast<float>(y)});
        world.assign(entity, ecs::Sprite{ "assets/28.png", ecs::Rectangle{0, 0, 210, 92}, ecs::Vector2{0, 0} });
        world.assign(entity, ecs::Acceleration{ 1, 0, 15 });
        world.assign(entity, ecs::Scale{ 0.25, 0.25 });
        world.assign(entity, ecs::Rotation{ 0 });
        world.assign(entity, ecs::Collision{ false, {}, true });
        world.assign(entity, ecs::Sound{ "assets/weird.wav" });
        world.assign(entity, ecs::Damage{ 10 });
    }
}
