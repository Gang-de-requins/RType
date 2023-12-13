#include "systems/Movement.hpp"
#include "World.hpp"

namespace ecs {
    void MovementSystem::update(World &world) {
        std::vector<Entity *> entities = world.view<Position, Velocity, Acceleration>();

        for (auto &entity : entities) {
            Position &position = world.get<Position>(*entity);
            Velocity &velocity = world.get<Velocity>(*entity);
            Acceleration &acceleration = world.get<Acceleration>(*entity);

            velocity.dx += acceleration.ddx;
            velocity.dy += acceleration.ddy;

            velocity.dx = std::clamp(velocity.dx, -acceleration.maxSpeed, acceleration.maxSpeed);
            velocity.dy = std::clamp(velocity.dy, -acceleration.maxSpeed, acceleration.maxSpeed);

            position.x += velocity.dx;
            position.y += velocity.dy;
        }
    }
}
