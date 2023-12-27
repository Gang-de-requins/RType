#include "systems/rendering/Rectangle.hpp"
#include "SceneManager.hpp"

namespace ecs {
    void RectangleSystem::update(SceneManager &sceneManager) {
        auto entities = sceneManager.view<Position, Rectangle, Scale, Rotation, Color>(sceneManager.getCurrentScene());

        for (auto &entity : entities) {
            auto &position = sceneManager.get<Position>(*entity);
            auto &rectangle = sceneManager.get<Rectangle>(*entity);
            auto &scale = sceneManager.get<Scale>(*entity);
            auto &rotation = sceneManager.get<Rotation>(*entity);
            auto &color = sceneManager.get<Color>(*entity);

            DrawRectanglePro(
                ::Rectangle{ position.x, position.y, rectangle.width * scale.x, rectangle.height * scale.y },
                ::Vector2{ rectangle.width / 2, rectangle.height / 2 },
                rotation.angle,
                ::Color{ color.r, color.g, color.b, color.a }
            );
        }
    }
}
