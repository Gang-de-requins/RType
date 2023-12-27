#include "systems/rendering/TextInput.hpp"
#include "SceneManager.hpp"

namespace ecs {
    void TextInputSystem::update(SceneManager &sceneManager) {
        auto entities = sceneManager.view<Text, TextInput>(sceneManager.getCurrentScene());

        for (auto &entity : entities) {
            auto &textInput = sceneManager.get<TextInput>(*entity);
            auto &text = sceneManager.get<Text>(*entity);

            if (textInput.isFocused) {
                std::cout << "Entity " << entity->id << " is focused" << std::endl;
                if (IsKeyPressed(KEY_ENTER)) {
                    textInput.isFocused = false;
                } else if (IsKeyPressed(KEY_BACKSPACE)) {
                    if (text.content.size() > 0) {
                        text.content.pop_back();
                    }
                } else {
                    int key = GetCharPressed();

                    if (text.content.size() >= textInput.maxLength) {
                        continue;
                    }

                    if (key >= 65 && key <= 90) {
                        text.content.push_back(key);
                    } else if (key >= 48 && key <= 57) {
                        text.content.push_back(key);
                    } else if (key == 32 || key == 95 || key == 45 || key == 46) {
                        text.content.push_back(key);
                    }
                }
            }
        }
    }
}
