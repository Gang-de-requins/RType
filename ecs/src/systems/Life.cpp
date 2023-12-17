#include "systems/Life.hpp"
#include "SceneManager.hpp"

namespace ecs {
    void LifeSystem::update(SceneManager &sceneManager) {
        std::vector<Entity *> entitiesHealth = sceneManager.view<Health, Collision>(sceneManager.getCurrentScene());
        std::vector<Entity *> entitiesDamage = sceneManager.view<Damage, Collision>(sceneManager.getCurrentScene());
        std::vector<Entity *> entitiesToDelete;

        for (auto &entityHealth : entitiesHealth) {
            Health &health = sceneManager.get<Health>(*entityHealth);
            Collision &collision = sceneManager.get<Collision>(*entityHealth);

            if (collision.isColliding) {
                for (auto &entityDamage : entitiesDamage) {
                    Damage &damage = sceneManager.get<Damage>(*entityDamage);

                    if (std::find(collision.collidingWith.begin(), collision.collidingWith.end(), entityDamage->id) != collision.collidingWith.end()) {
                        health.health -= damage.damage;
                        collision.collidingWith.erase(std::remove(collision.collidingWith.begin(), collision.collidingWith.end(), entityDamage->id), collision.collidingWith.end());
                        entitiesToDelete.emplace_back(entityDamage);
                    }

                    if (health.health <= 0) {
                        collision.collidingWith.erase(std::remove(collision.collidingWith.begin(), collision.collidingWith.end(), entityHealth->id), collision.collidingWith.end());
                        entitiesToDelete.emplace_back(entityHealth);
                    }
                }
            }

            collision.isColliding = false;
        }

        for (auto &entity : entitiesToDelete) {
            sceneManager.destroyEntity(sceneManager.getCurrentScene(), *entity);
        }
        entitiesToDelete.clear();
    }
}
