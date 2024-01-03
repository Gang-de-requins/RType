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
            if (IsKeyPressed(controllable.keySpace) && std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - controllable.shootUpdate).count() >= controllable.timeOut){
                auto entities = sceneManager.view<Sound>(sceneManager.getCurrentScene())[0];
                auto &sound = sceneManager.get<Sound>(*entities);
                auto &soundData = sceneManager.getSound(sound.path);

                actionFound = true;
                controllable.shootUpdate = std::chrono::steady_clock::now();
                PlaySound(soundData);
                Position &position = sceneManager.get<Position>(*entity);
                Sprite &sprite = sceneManager.get<Sprite>(*entity);
                Scale &scale = sceneManager.get<Scale>(*entity);
                Entity &Shoot = sceneManager.createEntity(sceneManager.getCurrentScene());
                sceneManager.assign(Shoot, Position{position.x + sprite.source.width * scale.x, position.y + (sprite.source.height / 2) * scale.y});
                sceneManager.assign(Shoot, Velocity{3, 0});
                sceneManager.assign(Shoot, Sprite{"assets/28.png", Rectangle{0, 0, 210, 92}, Vector2{0, 0}});
                sceneManager.assign(Shoot, Acceleration{0, 0, 15});
                sceneManager.assign(Shoot, Scale{0.25, 0.25});
                sceneManager.assign(Shoot, Rotation{0});;
                sceneManager.assign(Shoot, Collision{false, {}, true});
                sceneManager.assign(Shoot, Damage{10});

                scene.events[EventType::Input].push_back({
                    Event::Shoot,
                    {&Shoot}
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
