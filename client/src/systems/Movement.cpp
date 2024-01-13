#include "systems/Movement.hpp"
#include "SceneManager.hpp"

namespace ecs {
	void MovementSystem::update(SceneManager& sceneManager) {
        ecs::Scene& scene = sceneManager.getCurrentScene();
        int index = 0;
        std::vector<int> eventsToRemove = {};

        for (auto& event : scene.events.at(EventType::Input)) {
            switch (event.event) {
            case GameEvent::MoveUp:
                for (auto& entity : event.entities) {
                    Acceleration& acceleration = sceneManager.get<Acceleration>(*entity);
                    acceleration.ddx = 0;
                    acceleration.ddy = -0.5f;
                    acceleration.maxSpeed = 8.0f;

                    eventsToRemove.push_back(index);
                }
                break;
            case GameEvent::MoveDown:
                for (auto& entity : event.entities) {
                    Acceleration& acceleration = sceneManager.get<Acceleration>(*entity);
                    acceleration.ddx = 0;
                    acceleration.ddy = 0.5f;
                    acceleration.maxSpeed = 8.0f;

                    eventsToRemove.push_back(index);
                }
                break;
            case GameEvent::MoveLeft:
                for (auto& entity : event.entities) {
                    Acceleration& acceleration = sceneManager.get<Acceleration>(*entity);
                    acceleration.ddx = -0.5f;
                    acceleration.ddy = 0;
                    acceleration.maxSpeed = 8.0f;

                    eventsToRemove.push_back(index);
                }
                break;
            case GameEvent::MoveRight:
                for (auto& entity : event.entities) {
                    Acceleration& acceleration = sceneManager.get<Acceleration>(*entity);
                    acceleration.ddx = 0.5f;
                    acceleration.ddy = 0;
                    acceleration.maxSpeed = 8.0f;

                    eventsToRemove.push_back(index);
                }
                break;
            case GameEvent::StopMoving:
                for (auto& entity : event.entities) {
                    Acceleration& acceleration = sceneManager.get<Acceleration>(*entity);

                    acceleration.ddx *= -1;
                    acceleration.ddy *= -1;
                    acceleration.maxSpeed -= 0.1f;
                    acceleration.maxSpeed = std::max(acceleration.maxSpeed, 0.0f);

                    eventsToRemove.push_back(index);
                }
                break;
            default:
                break;
            }
            index++;
        }

        for (auto& entity : sceneManager.view<Acceleration, Velocity, Position>(scene)) {
            this->move(sceneManager, entity);

            if (sceneManager.has<Damage>(*entity)) {
                Position& position = sceneManager.get<Position>(*entity);

                if (position.x < 0 || position.x > 1920 || position.y < 0 || position.y > 1080) {
                    scene.events[EventType::Destroy].push_back({
                        Event::EntityDestroyed,
                        { entity }
                    });
				}
            }

        }

        for (auto& event : eventsToRemove) {
            scene.events.at(EventType::Input).erase(scene.events.at(EventType::Input).begin() + event);

            for (auto& i : eventsToRemove) {
                if (i > event) {
                    i--;
                }
            }
        }
	}

    void MovementSystem::move(SceneManager& sceneManager, Entity *entity) {
		Acceleration& acceleration = sceneManager.get<Acceleration>(*entity);
		Velocity& velocity = sceneManager.get<Velocity>(*entity);
		Position& position = sceneManager.get<Position>(*entity);

		velocity.dx += acceleration.ddx;
		velocity.dy += acceleration.ddy;

		velocity.dx = std::clamp(velocity.dx, -acceleration.maxSpeed, acceleration.maxSpeed);
		velocity.dy = std::clamp(velocity.dy, -acceleration.maxSpeed, acceleration.maxSpeed);

		position.x += velocity.dx;
		position.y += velocity.dy;
	}
}
