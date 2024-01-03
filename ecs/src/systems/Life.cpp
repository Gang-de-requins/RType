#include "systems/Life.hpp"
#include "SceneManager.hpp"

namespace ecs {
    void LifeSystem::update(SceneManager &sceneManager) {
        ecs::Scene &scene = sceneManager.getCurrentScene();
        std::vector<Entity *> entitiesHealth = sceneManager.view<Health, Collision>(scene);
        std::vector<Entity *> entitiesDamage = sceneManager.view<Damage, Collision>(scene);

        for (auto &entityHealth : entitiesHealth) {
            Collision &collision = sceneManager.get<Collision>(*entityHealth);

            if (collision.isColliding) {
                Health &health = sceneManager.get<Health>(*entityHealth);

                for (auto &entityDamage : entitiesDamage) {
                    Damage &damage = sceneManager.get<Damage>(*entityDamage);

                    if (std::find(collision.collidingWith.begin(), collision.collidingWith.end(), entityDamage->id) != collision.collidingWith.end()) {
                        health.health -= damage.damage;
                        collision.collidingWith.erase(std::remove(collision.collidingWith.begin(), collision.collidingWith.end(), entityDamage->id), collision.collidingWith.end());
                        // change event to check if entity is an enemy, sprite or something else
                        scene.events[EventType::Destroy].push_back({
                            Event::EnemyDeath,
                            {entityDamage}
                        });
                    }

                    if (health.health <= 0) {
                        collision.collidingWith.erase(std::remove(collision.collidingWith.begin(), collision.collidingWith.end(), entityHealth->id), collision.collidingWith.end());
                        if (sceneManager.has<Controllable>(*entityHealth)) {
                            scene.events[EventType::Destroy].push_back({
                                Event::PlayerDeath,
                                {entityHealth}
                            });
                        }
                    }
                }
            }

            collision.isColliding = false;
        }
    }
}
