#include "systems/Clickable.hpp"
#include "SceneManager.hpp"

namespace ecs {

    bool ClickableSystem::mouseInSprite(::Vector2 mousePosition, Entity &entitie, SceneManager &sceneManager) {
        Position &position = sceneManager.get<Position>(entitie);
        Scale &scale = sceneManager.get<Scale>(entitie) ;
        Sprite &sprite = sceneManager.get<Sprite>(entitie);
        Clickable &clickable = sceneManager.get<Clickable>(entitie);
        ::Rectangle rec {position.x, position.y, sprite.source.width * scale.x, sprite.source.height * scale.y};

        return (CheckCollisionPointRec(mousePosition, rec));
    }

    void ClickableSystem::update(SceneManager &sceneManager) {
        std::vector<Entity*> entities = sceneManager.view<Position, Sprite, Scale, Rotation, Clickable>(sceneManager.getCurrentScene());
        ::Vector2 mousePosition = GetMousePosition();

        for (auto &entity : entities) {
            Clickable &clickable = sceneManager.get<Clickable>(*entity);

            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && mouseInSprite(mousePosition, *entity, sceneManager)) {
                clickable.onClick(clickable);
            }
        }
    }
}
