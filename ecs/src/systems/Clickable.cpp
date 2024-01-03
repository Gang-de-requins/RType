#include "systems/Clickable.hpp"
#include "SceneManager.hpp"

namespace ecs {
    bool ClickableSystem::mouseInSprite(::Vector2 mousePosition, Entity &entity, SceneManager &sceneManager) {
        Position &position = sceneManager.get<Position>(entity);
        Scale &scale = sceneManager.get<Scale>(entity) ;
        ::Rectangle rec = {position.x, position.y, 0, 0};
        bool hasSprite = sceneManager.has<Sprite>(entity);
        bool hasRectangle = sceneManager.has<Rectangle>(entity);

        if (hasSprite) {
            Sprite &sprite = sceneManager.get<Sprite>(entity);
            rec.width = sprite.source.width * scale.x;
            rec.height = sprite.source.height * scale.y;
        } else if (!hasSprite && hasRectangle) {
            Rectangle &rectangle = sceneManager.get<Rectangle>(entity);
            rec.width = rectangle.width * scale.x;
            rec.height = rectangle.height * scale.y;
        }

        return (CheckCollisionPointRec(mousePosition, rec));
    }

    void ClickableSystem::update(SceneManager &sceneManager) {
        std::vector<Entity*> entities = sceneManager.view<Position, Scale, Clickable>(sceneManager.getCurrentScene());
        ::Vector2 mousePosition = GetMousePosition();
        ecs::Scene &scene = sceneManager.getCurrentScene();

        for (auto &entity : entities) {
            if (scene != sceneManager.getCurrentScene())
                break;

            Clickable &clickable = sceneManager.get<Clickable>(*entity);

            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && mouseInSprite(mousePosition, *entity, sceneManager)) {
                clickable.onClick(clickable);
            }
        }
    }
}
