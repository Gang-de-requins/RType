#include "systems/Parallax.hpp"
#include "SceneManager.hpp"

namespace ecs {
    void ParallaxSystem::update(SceneManager &sceneManager) {
        std::vector<Entity *> entities = sceneManager.view<Parallax, Position>(sceneManager.getCurrentScene());

        for (auto &entity : entities) {
            Parallax &parallax = sceneManager.get<Parallax>(*entity);
            Position &position = sceneManager.get<Position>(*entity);

            if (position.x <= -1920 && parallax.check == true) {
                position.x = 0;
            }
        }
    }
}
