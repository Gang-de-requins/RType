#include "systems/rendering/TextInput.hpp"
#include "SceneManager.hpp"

namespace ecs {
    void TextInputSystem::update(SceneManager &sceneManager) {
        auto entities = sceneManager.view<TextInput, FontSize, TextColor, Position>(sceneManager.getCurrentScene());

        for (auto &entity : entities) {
            auto &textInput = sceneManager.get<TextInput>(*entity);
            auto &position = sceneManager.get<Position>(*entity);
            auto &textColor = sceneManager.get<TextColor>(*entity);
            auto &fontSize = sceneManager.get<FontSize>(*entity);

            DrawTextEx(
                GetFontDefault(),
                textInput.content.c_str(),
                ::Vector2{ textInput.textPosition.x, textInput.textPosition.y },
                fontSize.size,
                4.0f,
                ::Color{ textColor.r, textColor.g, textColor.b, textColor.a }
            );

            if (textInput.isFocused) {
                this->isMouseOver(GetMousePosition(), *entity, sceneManager) ? SetMouseCursor(MOUSE_CURSOR_IBEAM) : SetMouseCursor(MOUSE_CURSOR_DEFAULT);

                DrawTextEx(
                    GetFontDefault(),
                    "_",
                    ::Vector2{ textInput.textPosition.x + MeasureText(textInput.content.c_str(), fontSize.size), textInput.textPosition.y },
                    fontSize.size,
                    4.0f,
                    ::Color{ textColor.r, textColor.g, textColor.b, textColor.a }
                );

                if (IsKeyPressed(KEY_ENTER)) {
                    textInput.isFocused = false;
                    textInput.counter = 0;
                } else if (IsKeyPressed(KEY_BACKSPACE)) {
                    if (textInput.content.size() > 0) {
                        textInput.content.pop_back();
                    }
                } else {
                    int key = GetCharPressed();

                    if (key == 0 || textInput.content.size() >= textInput.maxLength) {
                        continue;
                    }

                    if ((key >= 65 && key <= 90) || (key >= 97 && key <= 122)) {
                        textInput.content.push_back(key);
                    } else if (key >= 48 && key <= 57) {
                        textInput.content.push_back(key);
                    } else if (key == 32 || key == 95 || key == 45 || key == 46) {
                        textInput.content.push_back(key);
                    }
                }
            }
        }
    }

    bool TextInputSystem::isMouseOver(::Vector2 mousePosition, Entity &entity, SceneManager &sceneManager) {
        Position &position = sceneManager.get<Position>(entity);
        Scale &scale = sceneManager.get<Scale>(entity);
        TextInput &textInput = sceneManager.get<TextInput>(entity);
        Rectangle &rectangle = sceneManager.get<Rectangle>(entity);
        ::Rectangle rec {position.x, position.y, rectangle.width * scale.x, rectangle.height * scale.y};

        return (CheckCollisionPointRec(mousePosition, rec));
    }
}
