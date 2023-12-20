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
            } else if (IsKeyPressed(controllable.keySpace)) {
                auto entities = sceneManager.view<Sound>(sceneManager.getCurrentScene())[0];
                auto &sound = sceneManager.get<Sound>(*entities);
                auto &soundData = sceneManager.getSound(sound.path);
                PlaySound(soundData);
            } else {
                acceleration.ddx *= -1;
                acceleration.ddy *= -1;

                acceleration.maxSpeed -= 0.1f;
                acceleration.maxSpeed = std::max(acceleration.maxSpeed, 0.0f);
            }
        }
    }
}
