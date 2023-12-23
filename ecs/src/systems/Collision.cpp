#include "systems/Collision.hpp"
#include "SceneManager.hpp"

namespace ecs {
    void CollisionSystem::update(SceneManager &sceneManager) {
        std::vector<Entity *> entities = sceneManager.view<Collision, Position, Sprite>(sceneManager.getCurrentScene());

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
                    collision1.isColliding = true;
                    collision1.collidingWith.push_back(entity2->id);

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
