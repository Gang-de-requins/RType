/*
** EPITECH PROJECT, 2024
** RType [WSL : Ubuntu]
** File description:
** Collision
*/

#include "systems/Collision.hpp"
#include "SceneManager.hpp"

namespace ecs
{

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

                CollisionInfo collisionInfoEntity1 = {
                    sceneManager.get<Sprite>(*entity1),
                    sceneManager.get<Position>(*entity1),
                    sceneManager.get<Scale>(*entity1),
                    sceneManager.get<Rotation>(*entity1)
                };
                
                CollisionInfo collisionInfoEntity2 = {
                    sceneManager.get<Sprite>(*entity2),
                    sceneManager.get<Position>(*entity2),
                    sceneManager.get<Scale>(*entity2),
                    sceneManager.get<Rotation>(*entity2)
                };

                if (this->isColliding(collisionInfoEntity1, collisionInfoEntity2)) {
                    std::cout << "Collides !!" << std::endl;
                    ecs::Velocity &actualVel = sceneManager.get<ecs::Velocity>(*entity1);
                    ecs::Position &actualPosPlayer = sceneManager.get<ecs::Position>(*entity2);
                    ecs::Position &actualPosBall = sceneManager.get<ecs::Position>(*entity1);
                    if (sceneManager.get<Sprite>(*entity1).path == "../assets/pong_ball.png") {
                        actualVel.dx *= -1;
                        actualVel.dx += actualVel.dx < 0 ? -1 : 1;
                        // sceneManager.loadSounds({"../../assets/pong_sound.wav"});
                        // PlaySound("../../assets/pong_sound.wav");
                        if (actualPosBall.y >= actualPosPlayer.y && actualPosBall.y <= actualPosPlayer.y + (260 * 0.25)) {
                            actualVel.dy = -2;
                        }
                        else if (actualPosBall.y >= actualPosPlayer.y + (260 * 0.25) && actualPosBall.y <= actualPosPlayer.y + (260 * 0.5)) {
                            actualVel.dy = -1;
                        }
                        else if (actualPosBall.y > actualPosPlayer.y + (260 * 0.5) && actualPosBall.y <= actualPosPlayer.y + (260 * 0.75)) {
                            actualVel.dy = 1;
                        }
                        else if (actualPosBall.y > actualPosPlayer.y + (260 * 0.75) && actualPosBall.y <= actualPosPlayer.y + (260 * 1)) {
                            actualVel.dy = 2;
                        }
                    }
                }
            }
        }
    }

    bool CollisionSystem::isColliding(const CollisionInfo &collisionInfo1, const CollisionInfo &collisionInfo2) {
        ::Rectangle rectangle1 = {
            collisionInfo1.position.x,
            collisionInfo1.position.y,
            collisionInfo1.sprite.source.width * collisionInfo1.scale.x,
            collisionInfo1.sprite.source.height * collisionInfo1.scale.y
        };
        ::Rectangle rectangle2 = {
            collisionInfo2.position.x,
            collisionInfo2.position.y,
            collisionInfo2.sprite.source.width * collisionInfo2.scale.x,
            collisionInfo2.sprite.source.height * collisionInfo2.scale.y
        };

        return CheckCollisionRecs(rectangle1, rectangle2);
    }

}