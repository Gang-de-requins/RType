#include "systems/Submit.hpp"
#include "SceneManager.hpp"

namespace ecs {

    void SubmitSystem::update(SceneManager &sceneManager) {
        auto entities = sceneManager.view<Submit>(sceneManager.getCurrentScene());

        for (auto &entity : entities) {
            Submit &submit = sceneManager.get<Submit>(*entity);
            if (IsKeyPressed(submit.activationKey)) {
                submit.onSubmit(sceneManager, entity);
            }
        }
    }
}
