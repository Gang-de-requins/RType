#include "systems/rendering/Text.hpp"

namespace ecs {
    void RenderTextSystem::update() {
        for (std::shared_ptr<ecs::Archetype> archetype : this->_archetypes) {
            std::vector<Position> &positions = archetype->getComponentVector<Position>();
            std::vector<Text> &texts = archetype->getComponentVector<Text>();
            std::vector<myColor> &textColors = archetype->getComponentVector<myColor>();
            std::vector<FontSize> &textSizes = archetype->getComponentVector<FontSize>();

            for (std::size_t i = 0; i < positions.size(); ++i) {
                DrawTextEx(GetFontDefault(),
                    texts[i].content.c_str(),
                    { positions[i].x, positions[i].y },
                    textSizes[i].size,
                    0.0f,
                    Color { textColors[i].r, textColors[i].g, textColors[i].b, textColors[i].a });
            }
        }
    }
}
