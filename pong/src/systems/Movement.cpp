/*
** EPITECH PROJECT, 2024
** RType [WSL : Ubuntu]
** File description:
** Movement
*/

#include "systems/Movement.hpp"
#include "SceneManager.hpp"
#include "Events.hpp"

namespace ecs
{

    void MovementSystem::update(SceneManager &sceneManager)
    {
        ecs::Scene& scene = sceneManager.getCurrentScene();
        std::vector<Entity*> list = sceneManager.view<ecs::Position, ecs::Velocity>(scene);


        for (auto &entity : list) {
            ecs::Position &actualPos = sceneManager.get<ecs::Position>(*entity);
            ecs::Velocity &actualVel = sceneManager.get<ecs::Velocity>(*entity);

            actualPos.x += actualVel.dx;
            actualPos.y += actualVel.dy;
        }
    }
}