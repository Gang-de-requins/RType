#include "systems/Movement.hpp"
#include "SceneManager.hpp"

namespace ecs {
	void MovementSystem::update(SceneManager& sceneManager) {
        ecs::Scene& scene = sceneManager.getCurrentScene();
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
