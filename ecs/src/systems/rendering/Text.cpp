#include "systems/rendering/Text.hpp"
#include "World.hpp"

namespace ecs {
    void TextSystem::update(World &world) {
        auto entities = world.view<Position, Text, Color, FontSize>();

        for (auto entity : entities) {
            auto &position = world.get<Position>(*entity);
            auto &text = world.get<Text>(*entity);
            auto &color = world.get<Color>(*entity);
            auto &fontSize = world.get<FontSize>(*entity);

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
