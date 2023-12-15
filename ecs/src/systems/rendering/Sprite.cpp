#include "systems/rendering/Sprite.hpp"
#include "SceneManager.hpp"

namespace ecs {
    void SpriteSystem::update(SceneManager &sceneManager) {
        auto entities = sceneManager.view<Position, Sprite, Scale, Rotation>(sceneManager.getCurrentScene());

        for (auto entity : entities) {
            auto &position = sceneManager.get<Position>(*entity);
            auto &sprite = sceneManager.get<Sprite>(*entity);
            auto &scale = sceneManager.get<Scale>(*entity);
            auto &rotation = sceneManager.get<Rotation>(*entity);
            auto &texture = sceneManager.getTexture(sprite.path.c_str());

            DrawTexturePro(
                texture,
                ::Rectangle{ sprite.source.x, sprite.source.y, sprite.source.width, sprite.source.height },
                ::Rectangle{ position.x, position.y, sprite.source.width * scale.x, sprite.source.height * scale.y },
                ::Vector2{ sprite.origin.x, sprite.origin.y },
                rotation.angle,
                ::Color{ 255, 255, 255, 255 }
            );
        }
    }
}
