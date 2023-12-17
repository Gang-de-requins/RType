#include "systems/Movement.hpp"
#include "SceneManager.hpp"

namespace ecs {
    void MovementSystem::update(SceneManager &sceneManager) {
        std::vector<Entity *> entities = sceneManager.view<Position, Velocity, Acceleration>(sceneManager.getCurrentScene());

        for (auto &entity : entities) {
            Position &position = sceneManager.get<Position>(*entity);
            Velocity &velocity = sceneManager.get<Velocity>(*entity);
            Acceleration &acceleration = sceneManager.get<Acceleration>(*entity);

            velocity.dx += acceleration.ddx;
            velocity.dy += acceleration.ddy;

            velocity.dx = std::clamp(velocity.dx, -acceleration.maxSpeed, acceleration.maxSpeed);
            velocity.dy = std::clamp(velocity.dy, -acceleration.maxSpeed, acceleration.maxSpeed);

            position.x += velocity.dx;
            position.y += velocity.dy;
        }
    }
}
