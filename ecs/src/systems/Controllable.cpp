#include "systems/Controllable.hpp"
#include "World.hpp"

namespace ecs {
    void ControllableSystem::update(World &world) {
        std::vector<Entity *> entities = world.view<Controllable, Acceleration>();

        for (auto &entity : entities) {
            Controllable &controllable = world.get<Controllable>(*entity);
            Acceleration &acceleration = world.get<Acceleration>(*entity);

            if (IsKeyDown(controllable.keyUp)) {
                acceleration.ddx = 0;
                acceleration.ddy = -0.3f;
                acceleration.maxSpeed = 4.0f;
            } else if (IsKeyDown(controllable.keyDown)) {
                acceleration.ddx = 0;
                acceleration.ddy = 0.3f;
                acceleration.maxSpeed = 4.0f;
            } else if (IsKeyDown(controllable.keyLeft)) {
                acceleration.ddx = -0.3f;
                acceleration.ddy = 0;
                acceleration.maxSpeed = 4.0f;
            } else if (IsKeyDown(controllable.keyRight)) {
                acceleration.ddx = 0.3f;
                acceleration.ddy = 0;
                acceleration.maxSpeed = 4.0f;
            } else {
                acceleration.ddx *= -1;
                acceleration.ddy *= -1;

                acceleration.maxSpeed -= 0.1f;
                acceleration.maxSpeed = std::max(acceleration.maxSpeed, 0.0f);
            }
        }
    }
}
