#include "systems/rendering/Sprite.hpp"

namespace ecs {
    void RenderSpriteSystem::update() {
        for (std::shared_ptr<Archetype> archetype : this->_archetypes) {
            std::vector<Position>& positions = archetype->getComponentVector<Position>();
            std::vector<Sprite>& sprites = archetype->getComponentVector<Sprite>();
            std::vector<Scale>& scales = archetype->getComponentVector<Scale>();
            std::vector<Rect>& rects = archetype->getComponentVector<Rect>();

            for (std::size_t i = 0; i < positions.size(); ++i) {
                DrawTexturePro(sprites[i].texture,
                    { rects[i].x, rects[i].y, rects[i].width, rects[i].height },
                    { positions[i].x, positions[i].y, rects[i].width * scales[i].x, rects[i].height * scales[i].y },
                    { 0.0f, 0.0f },
                    0.0f,
                    WHITE);
            }
        }
    }
}
