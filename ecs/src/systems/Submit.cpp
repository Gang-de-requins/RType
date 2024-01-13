#include "systems/Submit.hpp"
#include "SceneManager.hpp"

namespace ecs {

    void SubmitSystem::update(SceneManager &sceneManager) {
        auto entities = sceneManager.view<Submit>(sceneManager.getCurrentScene());

        for (auto &entity : entities) {
            Submit &submit = sceneManager.get<Submit>(*entity);
            if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(submit.activationKey))) {
                submit.onSubmit(sceneManager, entity);
            }
        }
    }
}
