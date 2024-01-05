#include "systems/Controllable.hpp"
#include "SceneManager.hpp"

namespace ecs {
    void ControllableSystem::update(SceneManager &sceneManager) {
        ecs::Scene &scene = sceneManager.getCurrentScene();
        std::vector<Entity *> entities = sceneManager.view<Controllable, Acceleration>(scene);

        for (auto &entity : entities) {
            Controllable &controllable = sceneManager.get<Controllable>(*entity);
            bool actionFound = false;

            if (IsKeyDown(controllable.keyUp)) {
                actionFound = true;
                scene.events[EventType::Input].push_back({
                    Event::MoveUp,
                    {entity}
                });

            }
            if (IsKeyDown(controllable.keyDown)) {
                actionFound = true;
                scene.events[EventType::Input].push_back({
                    Event::MoveDown,
                    {entity}
                });
            }
            if (IsKeyDown(controllable.keyLeft)) {
                actionFound = true;
                scene.events[EventType::Input].push_back({
                    Event::MoveLeft,
                    {entity}
                });
            }
            if (IsKeyDown(controllable.keyRight)) {
                actionFound = true;
                scene.events[EventType::Input].push_back({
                    Event::MoveRight,
                    {entity}
                });
            }
            if (IsKeyPressed(controllable.keySpace) && std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - controllable.shootUpdate).count() >= controllable.timeOut){
                actionFound = true;
                controllable.shootUpdate = std::chrono::steady_clock::now();
                scene.events[EventType::Spawn].push_back({
                    Event::SpawnPlayerBullet,
                    {entity}
                });
            }
            if (!actionFound) {
                scene.events[EventType::Input].push_back({
                    Event::StopMoving,
                    {entity}
                });
            }
        }
    }
}
