#include "systems/Movement.hpp"
#include "SceneManager.hpp"

namespace ecs {
    void MovementSystem::update(SceneManager &sceneManager) {
        ecs::Scene &scene = sceneManager.getCurrentScene();

        for (auto &event : scene.events.at(EventType::Input)) {
            switch (event.event) {
                case Event::MoveUp:
                    for (auto &entity : event.entities) {
                        Acceleration &acceleration = sceneManager.get<Acceleration>(*entity);
                        acceleration.ddx = 0;
                        acceleration.ddy = -0.5f;
                        acceleration.maxSpeed = 8.0f;

                        // this->move(sceneManager, entity);
                    }
                    break;
                case Event::MoveDown:
                    for (auto &entity : event.entities) {
                        Acceleration &acceleration = sceneManager.get<Acceleration>(*entity);
                        acceleration.ddx = 0;
                        acceleration.ddy = 0.5f;
                        acceleration.maxSpeed = 8.0f;

                        // this->move(sceneManager, entity);
                    }
                    break;
                case Event::MoveLeft:
                    for (auto &entity : event.entities) {
                        Acceleration &acceleration = sceneManager.get<Acceleration>(*entity);
                        acceleration.ddx = -0.5f;
                        acceleration.ddy = 0;
                        acceleration.maxSpeed = 8.0f;

                        // this->move(sceneManager, entity);
                    }
                    break;
                case Event::MoveRight:
                    for (auto &entity : event.entities) {
                        Acceleration &acceleration = sceneManager.get<Acceleration>(*entity);
                        acceleration.ddx = 0.5f;
                        acceleration.ddy = 0;
                        acceleration.maxSpeed = 8.0f;

                        // this->move(sceneManager, entity);
                    }
                    break;
                case Event::StopMoving:
                    for (auto &entity : event.entities) {
                        Acceleration &acceleration = sceneManager.get<Acceleration>(*entity);

                        acceleration.ddx *= -1;
                        acceleration.ddy *= -1;
                        acceleration.maxSpeed -= 0.1f;
                        acceleration.maxSpeed = std::max(acceleration.maxSpeed, 0.0f);

                        // this->move(sceneManager, entity);
                    }
                    break;
                default:
                    break;
            }

            event.entities.clear();
        }
        scene.events.at(EventType::Input).clear();

        for (auto &entity : sceneManager.view<Acceleration, Velocity, Position>(scene)) {
            this->move(sceneManager, entity);
        }
    }

    void MovementSystem::move(SceneManager &sceneManager, Entity *entity) {
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
