#include "ControllableSystem.hpp"
#include "SceneManager.hpp"

namespace ecs {
    void ControllableSystemCustom::update(SceneManager &sceneManager) {
        Scene &scene = sceneManager.getCurrentScene();
        auto entities = sceneManager.view<PControllable>(scene);

        for (auto &entity : entities) {
            PControllable &controllable = sceneManager.get<PControllable>(*entity);
            bool actionFound = false;

            for (auto &action : controllable.actions) {
                if (IsKeyDown(action.first)) {
                    actionFound = true;
                    action.second(entity);
                }
            }

            if (!actionFound) {
                scene.events[DefaultEventType::Input].push_back({
                    CustomEvent::StopMoving,
                    {entity}
                });
            }
        }
    }
}
