#include "systems/rendering/Sprite.hpp"
#include "World.hpp"

namespace ecs {
    void SpriteSystem::update(World &world) {
        auto entities = world.view<Position, Sprite, Scale, Rotation>();

        for (auto entity : entities) {
            auto &position = world.get<Position>(*entity);
            auto &sprite = world.get<Sprite>(*entity);
            auto &scale = world.get<Scale>(*entity);
            auto &rotation = world.get<Rotation>(*entity);
            auto &texture = world.getTexture(sprite.path);

            DrawTexturePro(
                texture,
                ::Rectangle{ sprite.source.x, sprite.source.y, sprite.source.width, sprite.source.height },
                ::Rectangle{ position.x, position.y, sprite.source.width * scale.x, sprite.source.height * scale.y },
                ::Vector2{ sprite.origin.x, sprite.origin.y },
                rotation.angle,
                WHITE
            );
        }
    }
}
