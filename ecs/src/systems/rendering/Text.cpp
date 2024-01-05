#include "systems/rendering/Text.hpp"
#include "SceneManager.hpp"

namespace ecs {
    void TextSystem::update(SceneManager &sceneManager) {
        auto entities = sceneManager.view<Position, Text, TextColor, FontSize>(sceneManager.getCurrentScene());

        for (auto &entity : entities) {
            auto &position = sceneManager.get<Position>(*entity);
            auto &text = sceneManager.get<Text>(*entity);
            auto &textColor = sceneManager.get<TextColor>(*entity);
            auto &fontSize = sceneManager.get<FontSize>(*entity);

            DrawTextEx(
                GetFontDefault(),
                text.content.c_str(),
                ::Vector2{ position.x, position.y },
                fontSize.size,
                4.0f,
                ::Color{ textColor.r, textColor.g, textColor.b, textColor.a }
            );
        }
    }
}
