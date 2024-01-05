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

                    for (auto &event : scene.events[EventType::Collisionnnnnn]) {
                        if ((event.entities[0]->id == entity1->id && event.entities[1]->id == entity2->id) || (event.entities[0]->id == entity2->id && event.entities[1]->id == entity1->id)) {
                            alreadyColliding = true;
                            break;
                        }
                    }

                    if (!alreadyColliding) {
                        bool entity1Damage = sceneManager.has<Damage>(*entity1);
                        bool entity2Damage = sceneManager.has<Damage>(*entity2);
                        bool entity1Health = sceneManager.has<Health>(*entity1);
                        bool entity2Health = sceneManager.has<Health>(*entity2);

                        if (entity1Damage && entity2Health) {
                            scene.events[EventType::Collisionnnnnn].push_back({
                                Event::DealDamage,
                                {entity1, entity2}
                            });
                        }
                        if (entity2Damage && entity1Health) {
                            scene.events[EventType::Collisionnnnnn].push_back({
                                Event::DealDamage,
                                {entity2, entity1}
                            });
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
}
