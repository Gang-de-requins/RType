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

                Position &position1 = sceneManager.get<Position>(*entity1);
                Position &position2 = sceneManager.get<Position>(*entity2);
                Sprite &sprite1 = sceneManager.get<Sprite>(*entity1);
                Sprite &sprite2 = sceneManager.get<Sprite>(*entity2);

                if (isColliding(position1, sprite1, position2, sprite2)) {
                    collision1.isColliding = true;
                    collision1.collidingWith.push_back(entity2->id);

                    if (sceneManager.has<Velocity>(*entity1)) {
                        Velocity &velocity1 = sceneManager.get<Velocity>(*entity1);
                        velocity1.dx = 0;
                        velocity1.dy = 0;

                        float overlapX = (position1.x + sprite1.source.width) - position2.x;
                        float overlapY = (position1.y + sprite1.source.height) - position2.y;

                        if (std::abs(overlapX) < std::abs(overlapY)) {
                            position1.x -= overlapX / 2;
                            position2.x += overlapX / 2;
                        } else {
                            position1.y -= overlapY / 2;
                            position2.y += overlapY / 2;
                        }
                    }
                }
            }
        }
    }

    /* ------------------------- PRIVATE FUCNTIONS -------------------------- */

    bool CollisionSystem::isColliding(const Position &pos1, const Sprite &sprite1, const Position &pos2, const Sprite &sprite2) {
        return pos1.x < pos2.x + sprite2.source.width &&
            pos1.x + sprite1.source.width > pos2.x &&
            pos1.y < pos2.y + sprite2.source.height &&
            pos1.y + sprite1.source.height > pos2.y;
    }
}
