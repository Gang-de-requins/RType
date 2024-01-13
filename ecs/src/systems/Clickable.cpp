#include "systems/Clickable.hpp"
#include "SceneManager.hpp"

namespace ecs {
    bool ClickableSystem::mouseInSprite(sf::Vector2f mousePosition, Entity &entity, SceneManager &sceneManager) {
        Position &position = sceneManager.get<Position>(entity);
        Scale &scale = sceneManager.get<Scale>(entity) ;
        sf::FloatRect rec = {position.x, position.y, 0, 0};
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

        // return (CheckCollisionPointRec(mousePosition, rec));

        return rec.contains(mousePosition.x, mousePosition.y);
    }

    void ClickableSystem::update(SceneManager &sceneManager) {
        std::vector<Entity*> entities = sceneManager.view<Position, Scale, Clickable>(sceneManager.getCurrentScene());
        sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition());
        ecs::Scene &scene = sceneManager.getCurrentScene();

        for (auto &entity : entities) {
            if (scene != sceneManager.getCurrentScene())
                break;

            Clickable &clickable = sceneManager.get<Clickable>(*entity);

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouseInSprite(mousePosition, *entity, sceneManager)) {
                clickable.onClick(clickable);
            }
        }
    }
}
