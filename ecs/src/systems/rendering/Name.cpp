#include "systems/rendering/Name.hpp"
#include "SceneManager.hpp"

namespace ecs {
    void NameSystem::update(SceneManager &sceneManager) {
        auto entities = sceneManager.view<Name, Position>(sceneManager.getCurrentScene());

        for (auto &entity : entities) {
            auto &name = sceneManager.get<Name>(*entity);
            auto &position = sceneManager.get<Position>(*entity);

            DrawTextEx(
                GetFontDefault(),
                name.name.c_str(),
                ::Vector2{ position.x + name.position.x, position.y + name.position.y },
                20,
                0.0f,
                ::Color{ 255, 255, 255, 255 }
            );
        }
    }
}
