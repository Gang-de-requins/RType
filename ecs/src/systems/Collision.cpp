#include "systems/Collision.hpp"
#include "SceneManager.hpp"

namespace ecs {
    void CollisionSystem::update(SceneManager &sceneManager) {
        ecs::Scene &scene = sceneManager.getCurrentScene();
        std::vector<Entity *> entities = sceneManager.view<Collision, Position, Sprite>(scene);

        for (auto &entity1 : entities) {
            Collision &collision1 = sceneManager.get<Collision>(*entity1);
            collision1.collidingWith.clear();
            for (auto &entity2 : entities) {
                if (entity1 == entity2) {
                    continue;
                }

                CollisionInfo collisionInfo = {
                    sceneManager.get<Sprite>(*entity1),
                    sceneManager.get<Position>(*entity1),
                    sceneManager.get<Scale>(*entity1),
                    sceneManager.get<Rotation>(*entity1),
                    sceneManager.get<Sprite>(*entity2),
                    sceneManager.get<Position>(*entity2),
                    sceneManager.get<Scale>(*entity2),
                    sceneManager.get<Rotation>(*entity2)
                };

                Collision &collision2 = sceneManager.get<Collision>(*entity2);

                if (this->isColliding(collisionInfo)) {
                    bool alreadyColliding = false;
                    std::vector<std::function<bool(SceneManager &, Scene &, Entity *&, Entity *&, bool)>> collisionFunctions = {
                        std::bind(&CollisionSystem::isDamageCollision, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5),
                        std::bind(&CollisionSystem::isModifierCollision, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5)
                    };

                    for (auto &event : scene.events[EventType::Collisionnnnnn]) {
                        if ((event.entities[0]->id == entity1->id && event.entities[1]->id == entity2->id) || (event.entities[0]->id == entity2->id && event.entities[1]->id == entity1->id)) {
                            alreadyColliding = true;
                            break;
                        }
                    }

                    for (auto &collisionFunction : collisionFunctions) {
                        if (collisionFunction(sceneManager, scene, entity1, entity2, alreadyColliding)) {
                            break;
                        }
                    }                    


                    if (!collision1.isOverlap && !collision2.isOverlap && sceneManager.has<Velocity>(*entity1)) {
                        Velocity &velocity1 = sceneManager.get<Velocity>(*entity1);
                        velocity1.dx = 0;
                        velocity1.dy = 0;

                        float overlapX = (collisionInfo.position1.x + collisionInfo.sprite1.source.width) - collisionInfo.position2.x;
                        float overlapY = (collisionInfo.position1.y + collisionInfo.sprite1.source.height) - collisionInfo.position2.y;

                        if (std::abs(overlapX) < std::abs(overlapY)) {
                            collisionInfo.position1.x -= overlapX / 2;
                            collisionInfo.position2.x += overlapX / 2;
                        } else {
                            collisionInfo.position1.y -= overlapY / 2;
                            collisionInfo.position2.y += overlapY / 2;
                        }
                    }
                }
            }
        }
    }

    /* ------------------------- PRIVATE FUCNTIONS -------------------------- */

    bool CollisionSystem::isColliding(const CollisionInfo &collisionInfo) {
        ::Rectangle rectangle1 = {
            collisionInfo.position1.x,
            collisionInfo.position1.y,
            collisionInfo.sprite1.source.width * collisionInfo.scale1.x,
            collisionInfo.sprite1.source.height * collisionInfo.scale1.y
        };
        ::Rectangle rectangle2 = {
            collisionInfo.position2.x,
            collisionInfo.position2.y,
            collisionInfo.sprite2.source.width * collisionInfo.scale2.x,
            collisionInfo.sprite2.source.height * collisionInfo.scale2.y
        };

        return CheckCollisionRecs(rectangle1, rectangle2);
    }

    bool CollisionSystem::isDamageCollision(SceneManager &sceneManager, Scene &scene, Entity *&entity1, Entity *&entity2, bool alreadyColliding) {
        bool modification = false;

        if (!alreadyColliding) {
            bool entity1Damage = sceneManager.has<Damage>(*entity1);
            bool entity2Damage = sceneManager.has<Damage>(*entity2);
            bool entity1Shooter = sceneManager.has<Shooter>(*entity1);
            bool entity2Shooter = sceneManager.has<Shooter>(*entity2);
            bool entity1Health = sceneManager.has<Health>(*entity1);
            bool entity2Health = sceneManager.has<Health>(*entity2);

            if (entity1Damage && entity2Health && entity2Shooter) {
                if (entity1Health) {
                    ecs::Health &health = sceneManager.get<Health>(*entity1);

                    if (health.health <= 0) {
                        return false;
                    }
                }

                modification = true;
                scene.events[EventType::Collisionnnnnn].push_back({
                    Event::DealDamage,
                    {entity1, entity2}
                });
            }
            if (entity2Damage && entity1Health && entity1Shooter) {
                if (entity2Health) {
                    ecs::Health &health = sceneManager.get<Health>(*entity2);

                    if (health.health <= 0) {
                        return false;
                    }
                }

                modification = true;
                scene.events[EventType::Collisionnnnnn].push_back({
                    Event::DealDamage,
                    {entity2, entity1}
                });
            }
            if (entity1Damage && !entity1Health && !entity1Shooter && entity2Health && entity2Damage) {
                modification = true;
                scene.events[EventType::Collisionnnnnn].push_back({
                    Event::DealDamage,
                    {entity1, entity2}
                });
            }
        }

        return modification;
    }

    bool CollisionSystem::isModifierCollision(SceneManager &sceneManager, Scene &scene, Entity *&entity1, Entity *&entity2, bool alreadyColliding) {
        bool modification = false;

        if (!alreadyColliding) {
            bool entity1Modifier = sceneManager.has<Modifier>(*entity1);
            bool entity2Modifier = sceneManager.has<Modifier>(*entity2);

            if (entity1Modifier) {
                modification = true;
                scene.events[EventType::Collisionnnnnn].push_back({
                    Event::ApplyModifier,
                    {entity1, entity2}
                });
            }
            if (entity2Modifier) {
                modification = true;
                scene.events[EventType::Collisionnnnnn].push_back({
                    Event::ApplyModifier,
                    {entity2, entity1}
                });
            }
        }

        return modification;
    }
}
