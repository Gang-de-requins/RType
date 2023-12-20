#include "systems/Controllable.hpp"
#include "SceneManager.hpp"

namespace ecs {
    void ControllableSystem::update(SceneManager &sceneManager) {
        std::vector<Entity *> entities = sceneManager.view<Controllable, Acceleration>(sceneManager.getCurrentScene());

        for (auto &entity : entities) {
            Controllable &controllable = sceneManager.get<Controllable>(*entity);
            Acceleration &acceleration = sceneManager.get<Acceleration>(*entity);

            if (IsKeyDown(controllable.keyUp)) {
                acceleration.ddx = 0;
                acceleration.ddy = -0.3f;
                acceleration.maxSpeed = 4.0f;
            } else if (IsKeyDown(controllable.keyDown)) {
                acceleration.ddx = 0;
                acceleration.ddy = 0.3f;
                acceleration.maxSpeed = 4.0f;
            } else if (IsKeyDown(controllable.keyLeft)) {
                acceleration.ddx = -0.3f;
                acceleration.ddy = 0;
                acceleration.maxSpeed = 4.0f;
            } else if (IsKeyDown(controllable.keyRight)) {
                acceleration.ddx = 0.3f;
                acceleration.ddy = 0;
                acceleration.maxSpeed = 4.0f;
            } else if (IsKeyPressed(controllable.keySpace) && std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - controllable.shootUpdate).count() >= controllable.timeOut){
                auto entities = sceneManager.view<Sound>(sceneManager.getCurrentScene())[0];
                auto &sound = sceneManager.get<Sound>(*entities);
                auto &soundData = sceneManager.getSound(sound.path);

                PlaySound(soundData);
                Position &position = sceneManager.get<Position>(*entity);
                Sprite &sprite = sceneManager.get<Sprite>(*entity);
                Entity &Shoot = sceneManager.createEntity(sceneManager.getCurrentScene());
                sceneManager.assign(Shoot, Position{position.x + sprite.source.width, position.y});
                sceneManager.assign(Shoot, Velocity{3, 0});
                sceneManager.assign(Shoot, Sprite{"assets/28.png", Rectangle{0, 0, 210, 92}, Vector2{0, 0}});
                sceneManager.assign(Shoot, Acceleration{0, 0, 15});
                sceneManager.assign(Shoot, Scale{0.25, 0.25});
                sceneManager.assign(Shoot, Rotation{0});;
                sceneManager.assign(Shoot, Collision{false, {}});
                sceneManager.assign(Shoot, Damage{10});
            } else {
                acceleration.ddx *= -1;
                acceleration.ddy *= -1;

                acceleration.maxSpeed -= 0.1f;
                acceleration.maxSpeed = std::max(acceleration.maxSpeed, 0.0f);
            }
        }
    }
}
