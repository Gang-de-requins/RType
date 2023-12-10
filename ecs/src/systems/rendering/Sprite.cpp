#include "systems/rendering/Sprite.hpp"

namespace ecs {
    void RenderSpriteSystem::update(World &world) {
        for (std::shared_ptr<Archetype> archetype : this->_archetypes) {
            std::vector<Position>& positions = archetype->getComponentVector<Position>();
            std::vector<Sprite>& sprites = archetype->getComponentVector<Sprite>();
            std::vector<Scale>& scales = archetype->getComponentVector<Scale>();
            // std::vector<Rect>& rects = archetype->getComponentVector<Rect>();

            for (std::size_t i = 0; i < positions.size(); ++i) {
                DrawTexturePro(sprites[i].texture,
                    { sprites[i].source.x, sprites[i].source.y, sprites[i].source.width, sprites[i].source.height },
                    { positions[i].x, positions[i].y, sprites[i].source.width * scales[i].x, sprites[i].source.height * scales[i].y },
                    sprites[i].origin,
                    0.0f,
                    WHITE);
            }
        }
    }
}
