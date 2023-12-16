#include "systems/rendering/Text.hpp"
#include "SceneManager.hpp"

namespace ecs {
    void TextSystem::update(SceneManager &sceneManager) {
        auto entities = sceneManager.view<Position, Text, Color, FontSize>(sceneManager.getCurrentScene());

        for (auto entity : entities) {
            auto &position = sceneManager.get<Position>(*entity);
            auto &text = sceneManager.get<Text>(*entity);
            auto &color = sceneManager.get<Color>(*entity);
            auto &fontSize = sceneManager.get<FontSize>(*entity);

            DrawTextEx(
                GetFontDefault(),
                text.content.c_str(),
                ::Vector2{ position.x, position.y },
                fontSize.size,
                0.0f,
                ::Color{ color.r, color.g, color.b, color.a }
            );
        }
    }
}
